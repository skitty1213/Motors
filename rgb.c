

#include "rgb.h"

RGB_DATA rgbData;
uint8_t value = 0x01;
uint8_t value2 = 0x03;
bool initialize = true;


void RGB_Initialize ( void )
{
    //DRV_I2C0_Initialize();
    //DRV_I2C0_BaudRateSet(115200);
   // startI2C();
    //startI2C();
           // writeConfig(0x00,0x46);
            //stopI2C();
           uint8_t res1 = 0;
        startI2C();
        sendRequest(0x00);
        res1 = readbyte(true);
        //sendValueAlot(res1);
        stopI2C();
        
        startI2C();
            writeConfig(0x00,0x46);
            stopI2C();
           //DRV_I2C0_MasterStop();
            uint8_t r = 0;
            startI2C();
            sendRequest(0x01);
            r = readbyte(true);
            
            stopI2C();
           // DRV_I2C0_MasterStop();
            
           // sendRequest(0x01);
            //r |= readbyte(false);
           // r |= readbyte(false);
           // r |= readbyte(false);
            char s[6] = "aaaaaa";
            s[5] = r;
            //sendMessage(s);
            
            //sendMessage("CONFIG");
            startI2C();
            writeConfig(0x01,0x01);
            stopI2C();
           //DRV_I2C0_MasterStop();
            startI2C();
            writeConfig(0x02,0x3F);
            stopI2C();
           //DRV_I2C0_MasterStop();
            startI2C();
            writeConfig(0x03,0x00);
            stopI2C();
           //DRV_I2C0_MasterStop();
            //stopI2C();
            
            
            startI2C();
            sendRequest(0x01);
            r = readbyte(true);
            
            stopI2C();
            s[5] = r;
            //sendMessage(s);
            if (r != 0x01)
                initialize = true;
            
            startI2C();
            writeConfig(0x02,0x3F);
            stopI2C();    
   /* uint8_t res = 0;
   startI2C();
        sendRequest(0x00);
        uint8_t res1 = readbyte(true);
       res1 = readbyte(true);
       sendValueAlot(res1);
        stopI2C();*/
        //sendMessage("start_");
}

void sendRequest(uint8_t data)
{
    
    while (!DRV_I2C0_MasterBusIdle());
    
    
   !DRV_I2C0_ByteWrite(0x88); 
    DRV_I2C0_WaitForByteWriteToComplete(); 
    while(!DRV_I2C0_WriteByteAcknowledged());

    while (!DRV_I2C0_MasterBusIdle());
    
    DRV_I2C0_ByteWrite(data); 
    DRV_I2C0_WaitForByteWriteToComplete(); 
    while(!DRV_I2C0_WriteByteAcknowledged());
    
    startI2C();
    
    while (!DRV_I2C0_MasterBusIdle());
    
    DRV_I2C0_ByteWrite(0x89); 
    DRV_I2C0_WaitForByteWriteToComplete(); 
    while(!DRV_I2C0_WriteByteAcknowledged());
    
}
void acquireDevice(void)
{
    uint8_t result = 0x00;
    while(result != 0x7D)
    {
        startI2C();
        sendRequest(0x00);
        
    }
}
void sendMessage(char* m)
{
    addQSnd('~');
    int i;
    for(i = 0; i < 6; i++)
        if(m[i])
            addQSnd(m[i]);
        else
            addQSnd(' ');
    addQSnd(')');
}

void writeConfig(uint8_t add, uint8_t data)
{
    while (!DRV_I2C0_MasterBusIdle());
    
    DRV_I2C0_ByteWrite(0x88); 
    DRV_I2C0_WaitForByteWriteToComplete(); 
    while(!DRV_I2C0_WriteByteAcknowledged());

    
    while (!DRV_I2C0_MasterBusIdle());
    
    DRV_I2C0_ByteWrite(add); 
    DRV_I2C0_WaitForByteWriteToComplete(); 
    while(!DRV_I2C0_WriteByteAcknowledged());
    
    
    while (!DRV_I2C0_MasterBusIdle());
    
    DRV_I2C0_ByteWrite(data); 
    DRV_I2C0_WaitForByteWriteToComplete(); 
    while(!DRV_I2C0_WriteByteAcknowledged());
    
    stopI2C();
    DRV_I2C0_MasterStop();
}
void sendValueAlot(uint8_t data)
{
    addQSnd('?'); 
    addQSnd(data);
    addQSnd(data); 
    addQSnd(data); 
    addQSnd(data); 
    addQSnd(data); 
    addQSnd(data); 
    addQSnd('?'); 
}
void RGB_Tasks ( void )
{
    uint8_t val = 0;
    /*if(initialize && 0)
    {
        uint8_t res1 = 0;
        startI2C();
        sendRequest(0x00);
        res1 = readbyte(true);
        sendValueAlot(res1);
        stopI2C();
        //res1 = readbyte(true);
        initialize = (res1 != 0x7D);
        //DRV_I2C0_MasterStop();
        if(!initialize)
        {
            sendMessage("Reset!");
            startI2C();
            writeConfig(0x00,0x46);
            stopI2C();
           //DRV_I2C0_MasterStop();
            uint8_t r = 0;
            startI2C();
            sendRequest(0x01);
            r = readbyte(true);
            
            stopI2C();
           // DRV_I2C0_MasterStop();
            
           // sendRequest(0x01);
            //r |= readbyte(false);
           // r |= readbyte(false);
           // r |= readbyte(false);
            char s[6] = "aaaaaa";
            s[5] = r;
            sendMessage(s);
            
            //sendMessage("CONFIG");
            startI2C();
            writeConfig(0x01,0x01);
            stopI2C();
           //DRV_I2C0_MasterStop();
            startI2C();
            writeConfig(0x02,0x3F);
            stopI2C();
           //DRV_I2C0_MasterStop();
            startI2C();
            writeConfig(0x03,0x00);
            stopI2C();
           //DRV_I2C0_MasterStop();
            //stopI2C();
            
            
            startI2C();
            sendRequest(0x01);
            r = readbyte(true);
            
            stopI2C();
           // DRV_I2C0_MasterStop();
            
           // sendRequest(0x01);
            //r |= readbyte(false);
           // r |= readbyte(false);
           // r |= readbyte(false);
            s[5] = r;
            sendMessage(s);
            if (r != 0x01)
                initialize = true;
            
            startI2C();
            writeConfig(0x02,0x3F);
            stopI2C();    
        }
        return;      
    }*/
    //sendMessage("ReadIT");
    //addQSnd(value); 
   // addQSnd('a'); 
    //addQSnd(value2); addQSnd(value2); addQSnd(value2); addQSnd(value2); addQSnd(value2); addQSnd(value2); 
    
    startI2C(); 
    sendRequest(0x09);
    val = readbyte(false); 
    sendValueAlot(val);
    val = readbyte(true);
    sendValueAlot(val);
    DRV_I2C0_MasterStop();

    PLIB_INT_SourceEnable(INT_ID_0, INT_SOURCE_USART_1_TRANSMIT);  
     //sendMessage("ENDLOP");    
}

uint16_t getGreen(void)
{
    uint16_t val = 0;
    startI2C(); 
    sendRequest(0x09);
    val = readbyte(false); //low byte
    //sendValueAlot(val);
    val += readbyte(true) << 8; // high byte
    //sendValueAlot(val);
    DRV_I2C0_MasterStop();
        
    PLIB_INT_SourceEnable(INT_ID_0, INT_SOURCE_USART_1_TRANSMIT); 
    return val;
}

void startI2C ()
{
    while (!DRV_I2C0_MasterBusIdle());
    //DRV_I2C0_Initialize();
    //DRV_I2C0_BaudRateSet(115200);
    DRV_I2C0_MasterStart();
    //DRV_I2C0_WaitForStartComplete();
}
void stopI2C()
{
    while (!DRV_I2C0_MasterBusIdle());
    DRV_I2C0_MasterStop();
    DRV_I2C0_WaitForStopComplete();
}
void restartI2C()
{
    //DRV_I2C0_MasterBusIdle(); 
    DRV_I2C0_MasterRestart();
    ////DRV_I2C0_WaitForStartComplete();
}

uint8_t readbyte(bool last)
{
    while (!DRV_I2C0_MasterBusIdle());
    
    uint8_t temp;
    if(!DRV_I2C0_SetUpByteRead()) return 0;
    while(!DRV_I2C0_WaitForReadByteAvailable());
    temp =  DRV_I2C0_ByteRead();
    if(!last)
    {
        DRV_I2C0_MasterACKSend();
       
    }
    while(! DRV_I2C0_WaitForACKOrNACKComplete());
    return temp; 
}

void writebyte(uint8_t temp)
{
    while (!DRV_I2C0_MasterBusIdle());
    
    //DRV_I2C0_MasterBusIdle();
    DRV_I2C0_ByteWrite(temp); 
    DRV_I2C0_WaitForByteWriteToComplete(); 
    while(!DRV_I2C0_WriteByteAcknowledged());
}



/*
void startI2C() {
    
    while (!DRV_I2C0_MasterBusIdle());
    DRV_I2C0_MasterStart();
    //while(I2C1CONbits.SEN);
    DRV_I2C0_WaitForStartComplete();
}

void stopI2C() {

    while (!DRV_I2C0_MasterBusIdle());
    DRV_I2C0_MasterStop();
    //while(I2C1CONbits.PEN);
    DRV_I2C0_WaitForStopComplete();
}

void repeatI2C() {
    
    while (!DRV_I2C0_MasterBusIdle());
    DRV_I2C0_MasterRestart();
    //while(I2C1CONbits.SEN);
    DRV_I2C0_WaitForStartComplete();
}
/*
void sendI2C(uint8_t data) {
    
    while (!DRV_I2C0_MasterBusIdle());
    DRV_I2C0_ByteWrite(data);
    while (!PLIB_I2C_TransmitterByteHasCompleted(I2C_ID_1));
    //DRV_I2C0_WaitForByteWriteToComplete();
    while(!DRV_I2C0_WriteByteAcknowledged()); 
}

uint8_t readI2C(uint8_t value) {
    
    while (!DRV_I2C0_MasterBusIdle());
    uint8_t data;
    value = (0x7D | 0x1); 
    sendI2C(value);
    data = DRV_I2C0_ByteRead();
    DRV_I2C0_MasterACKSend(); 
    while (!DRV_I2C0_WaitForACKOrNACKComplete());   
    return data;
}
 


void sendI2C(uint8_t data)
{
    //startI2C(); 
    DRV_I2C0_MasterStart();
    //Write address write
    DRV_I2C0_ByteWrite(0x00);
    DRV_I2C0_WaitForByteWriteToComplete();

    //Write command
    DRV_I2C0_ByteWrite(data);
    DRV_I2C0_WaitForByteWriteToComplete();

    //Stop i2c
    //stopI2C();
    DRV_I2C0_MasterStop();
}

uint8_t readI2C(uint8_t data) {
 uint16_t value;

    //Send Prom address
    sendI2C(data);

    //Start i2c
    DRV_I2C0_MasterStart();
    //startI2C(); 
    //Write address read
    DRV_I2C0_ByteWrite(0x00);
    DRV_I2C0_WaitForByteWriteToComplete();

    //Byte read MSB
    DRV_I2C0_WaitForReadByteAvailable();
    value = 256 * DRV_I2C0_ByteRead ();
    DRV_I2C0_MasterACKSend();

    //Byte read LSB
    DRV_I2C0_WaitForReadByteAvailable();
    value = DRV_I2C0_ByteRead();
    DRV_I2C0_MasterNACKSend();

    //Stop i2c
    DRV_I2C0_MasterStop();
    //stopI2C();
    return value;    
}

*/
