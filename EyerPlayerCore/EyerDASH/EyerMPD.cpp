#include "EyerMPD.hpp"
#include <libxml2/libxml/parser.h>
#include "EyerAdaptationSet.hpp"

namespace Eyer
{
    EyerMPD::EyerMPD()
    {

    }

    EyerMPD::~EyerMPD()
    {
        for(int i=0;i<adaptationSetList.size();i++){
            delete adaptationSetList[i];
        }
        adaptationSetList.clear();
    }

    int EyerMPD::SetBaseURL(EyerString & baseURL)
    {
        return 0;
    }

    int EyerMPD::GetInitURL(EyerString & url, int representationIndex)
    {
        EyerAdaptationSet videoAdaptationSet;
        int ret = GetVideoAdaptationSet(videoAdaptationSet);
        if(ret){
            return -1;
        }

        EyerSegmentTemplate segmentTemplate;
        ret = videoAdaptationSet.GetSegmentTemplate(segmentTemplate);
        if(ret){
            return -1;
        }

        EyerString initialization = baseUrl + segmentTemplate.GetInitialization();
        // EyerLog("initializationTemplate: %s\n", initialization.str);

        if(representationIndex >= videoAdaptationSet.GetRepresentationSize()){
            return -2;
        }

        EyerString representationId = videoAdaptationSet.GetRepresentation(representationIndex).GetId();
        initialization.Replace("$RepresentationID$", representationId);

        url = initialization;

        return 0;
    }

    int EyerMPD::GetVideoURL(EyerString & url, int number, int representationIndex)
    {
        EyerAdaptationSet videoAdaptationSet;
        int ret = GetVideoAdaptationSet(videoAdaptationSet);
        if(ret){
            return -1;
        }

        EyerSegmentTemplate segmentTemplate;
        ret = videoAdaptationSet.GetSegmentTemplate(segmentTemplate);
        if(ret){
            return -1;
        }

        EyerString media = segmentTemplate.GetMedia();
        EyerString mediaUrl = baseUrl + media;

        if(representationIndex >= videoAdaptationSet.GetRepresentationSize()){
            return -2;
        }

        EyerString representationId = videoAdaptationSet.GetRepresentation(representationIndex).GetId();
        // EyerLog("representationId: %s\n", representationId.str);

        mediaUrl.Replace("$RepresentationID$", representationId);
        mediaUrl.Replace("$Number$", Eyer::EyerString::Number(number));

        // EyerLog("media url: %s\n", mediaUrl.str);

        url = mediaUrl;

        return 0;
    }

    int EyerMPD::LoadMPD(EyerBuffer & buffer)
    {
        int finalRet = 0;

        int bufferLen = buffer.GetBuffer(nullptr);
        // EyerLog("mpd file length: %d\n", bufferLen);

        char * xmlStr = (char *)malloc(bufferLen);
        buffer.GetBuffer((unsigned char *)xmlStr);

        // printf("%s\n", xmlStr);


        // 解析 Xml
        xmlDocPtr pDoc = nullptr;
        xmlNodePtr pRoot = nullptr;

        xmlNode * node = nullptr;

        pDoc = xmlReadMemory(xmlStr, bufferLen, NULL, NULL, XML_PARSE_NOBLANKS);

        if (nullptr == pDoc) {
            fprintf(stderr,"Document not parsed successfully. \n");
            finalRet = -1;
            goto END;
        }

        pRoot = xmlDocGetRootElement(pDoc);
        if (nullptr == pRoot) {
            fprintf(stderr,"empty document\n");
            finalRet = -1;
            goto END;
        }

        for(xmlNode * node = pRoot->children; node; node = node->next) {
            if (xmlStrcasecmp(node->name, BAD_CAST "BaseURL") == 0) {
                baseUrl = (char *)xmlNodeGetContent(node);
            }
            if (xmlStrcasecmp(node->name, BAD_CAST "Period") == 0) {
                // AdaptationSet
                xmlNode * adaptationSetNode = nullptr;
                for(adaptationSetNode = node->children; adaptationSetNode; adaptationSetNode = adaptationSetNode->next){
                    EyerAdaptationSet * adaptationSet = new EyerAdaptationSet();
                    adaptationSet->LoadFromXML(adaptationSetNode);
                    adaptationSetList.push_back(adaptationSet);
                }
            }
        }

END:
        if(pDoc != nullptr){
            xmlFreeDoc(pDoc);
            pDoc = nullptr;
        }
        if(xmlStr != nullptr){
            free(xmlStr);
            xmlStr = nullptr;
        }
        return finalRet;
    }

    int EyerMPD::PrintInfo()
    {
        int ret = 0;
        printf("<===========================MPD Start===========================>\n");
        printf("\tBaseURL: %s\n", baseUrl.str);
        printf("\tPeriod:\n");
        for(int i=0;i<adaptationSetList.size();i++){
            printf("\t\tAdaptationSet:\n");
            EyerAdaptationSet * adaptationSet = adaptationSetList[i];
            printf("\t\t\tContent Type:%s\n", adaptationSet->GetContentType().str);

            EyerSegmentTemplate segmentTemplate;
            ret = adaptationSet->GetSegmentTemplate(segmentTemplate);
            if(ret){
                continue;
            }
            printf("\t\t\tSegmentTemplate:\n");
            printf("\t\t\t\tinitialization: %s\n", segmentTemplate.GetInitialization().str);
            printf("\t\t\t\tmedia: %s\n", segmentTemplate.GetMedia().str);

            int repSize = adaptationSet->GetRepresentationSize();
            for(int repId = 0; repId < repSize; repId++){
                EyerRepresentation representation = adaptationSet->GetRepresentation(repId);
                printf("\t\t\tRepresentation:\n");
                printf("\t\t\t\tid: %s\n", representation.GetId().str);
            }
        }
        printf("<=========================== MPD End ===========================>\n");
        return 0;
    }

    int EyerMPD::GetVideoAdaptationSet(EyerAdaptationSet & videoAdaptationSet)
    {
        for(int i=0;i<adaptationSetList.size();i++) {
            EyerAdaptationSet *adaptationSet = adaptationSetList[i];
            if(adaptationSet->GetContentType() == "video"){
                videoAdaptationSet = *adaptationSet;
                return 0;
            }
        }
        return -1;
    }

    int EyerMPD::GetAudioAdaptationSet(EyerAdaptationSet & audioAdaptationSet)
    {
        for(int i=0;i<adaptationSetList.size();i++) {
            EyerAdaptationSet *adaptationSet = adaptationSetList[i];
            if(adaptationSet->GetContentType() == "audio"){
                audioAdaptationSet = *adaptationSet;
                return 0;
            }
        }
        return -1;
    }
}