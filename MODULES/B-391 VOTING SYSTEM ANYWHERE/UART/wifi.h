#ifndef _WIFI
#define _WIFI


extern void intWIFI( );

extern void WIFI_CONNECT_Response(unsigned char *response);
extern void recvResponse(unsigned char *response);
extern void WIFI_RECEIVE_IP(unsigned char *response);
extern void Receive_Data(unsigned char *response);


extern void WIFI_UPLOAD_1(void);
extern void WIFI_UPLOAD_2(void);
extern void WIFI_UPLOAD_3(void);
extern void WIFI_UPLOAD_4(void);

extern void WIFI_UPLOAD_WHEET(void);
extern void WIFI_UPLOAD_RICE(void);
extern void WIFI_UPLOAD_KRS(void);
extern void WIFI_UPLOAD_DISPENSE(void);

#endif 
