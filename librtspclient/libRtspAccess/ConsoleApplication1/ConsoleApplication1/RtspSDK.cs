using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.InteropServices;

namespace vfw
{
    public enum STREAM_OVER_PROTOCOL
    {
        STREAMING_OVER_UDP = 0,
        STREAMING_OVER_TCP
    }

    public class RtspSDK
    {
        /// <summary>
        /// ��ȡrtsp ��Ƶ�� int RTSP_StartStream(const char* pRtspUrl,void* pUserData, STREAM_OVER_PROTOCOL Stream_Over_Protocol)
        /// 
        /// �磺int ret =RTSP_StartStream("rtsp://192.168.1.212:8556/PSIA/Streaming/channels/2?videoCodecType=H.264",NULL);
        /// ���һ������Stream_Over_ProtocolĬ��Ϊʹ��UDP�����Բ��
        /// ����ֵΪΨһ��ʾһ�����Ŀͻ���id������-1Ϊ����
        /// </summary>
        /// <param name="videoinfo"></param>
        /// <returns></returns>
        [DllImport("libRtspAccess.dll")]
        public static extern int RTSP_StartStream(string pRtspUrl,IntPtr pUserData, STREAM_OVER_PROTOCOL Stream_Over_Protocol);

        /// <summary>
        /// ֹͣrtsp��Ƶ�����Ͽ����ӡ�int RTSP_StopStream(int id);
        /// �����Ψһ��ʾһ�����Ŀͻ���id��
        /// </summary>
        /// <returns></returns>
        [DllImport("libRtspAccess.dll")]
        public static extern int RTSP_StopStream(int id);

        /// <summary>
        /// ����һ�����ͻ��˵Ļص�������void RTSP_SetCallBack(AVDataCallBackFuction avDataCallBack,int id);
        /// avDataCallBackΪ�ص��������������£�
        /// typedef int (CALLBACK *AVDataCallBackFuction)(int iAVSelect, char* pAVData, int iDataLen, int iWidth, int iHeight, int SessionID, void* pUserData);
        /// id ΪRTSP_StartStream�ķ���ֵ��
        /// </summary>
        /// <param name="avDataCallBack"></param>
        /// <param name="id"></param>
        [DllImport("libRtspAccess.dll")]
        public static extern void RTSP_SetCallBack(AVDataCallBackFuction avDataCallBack, int id);

        /// <summary>
        /// typedef int (CALLBACK *AVDataCallBackFuction)(int iAVSelect, char* pAVData, int iDataLen, int iWidth, int iHeight, int SessionID, void* pUserData);
        /// </summary>
        /// <param name="iAVSelect"></param>
        /// <param name="pAVData"></param>
        /// <param name="iDataLen"></param>
        /// <param name="iWidth"></param>
        /// <param name="iHeight"></param>
        /// <param name="SessionID"></param>
        /// <param name="pUserData"></param>
        //public delegate void AVDataCallBackFuction(int iAVSelect, IntPtr pAVData, int iDataLen, int iWidth, int iHeight, int SessionID, IntPtr pUserData);
        public delegate void AVDataCallBackFuction(IntPtr pAVData, int iDataLen, int iWidth, int iHeight);
    }
}
