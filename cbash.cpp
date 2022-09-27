#include "cbash.h"
#include<QByteArray>
#include <QBuffer>
#include <QDataStream>
Cbash::Cbash(int L, uint64_t sizeFile)
{
    this->SizeFile = sizeFile;
    this->l = L;
    if(l==192)
    {
       sizeBlock = 768;
        Ls = 0x30;

    }
    else if (l == 256)
    {
        sizeBlock = 512;
         Ls = 0x40;
    }
    else
    {
        sizeBlock = 1024;
         Ls = 0x20;
    }
    for (int i =0;i<192;i++)
    {
        //  S.insert(i,T0);
        if (i==184)
        {
             S.insert(184,Ls);
        }
        else
        {
            S.insert(i,T0);
        }

    }
}
void Cbash::BashHash (QByteArray X)
{
    //initilization
    QByteArray Xi;
  //  QByteArray S;
   // QByteArray Y;
    /*char Ls;
    char T0 = 0x00;
    int sizeBlock;
    int sizeInform;*/
 /*   this->l = L;
    if(l==192)
    {
       sizeBlock = 768;
        Ls = 0x30;
    }
    else if (l == 256)
    {
        sizeBlock = 512;
         Ls = 0x40;
    }
    else
    {
        sizeBlock = 1024;
         Ls = 0x20;
    }*/

    int Xlength = X.length();


    //step 1
   // QByteArray Xbash;
    if(SizeFile<=uint64_t(Xlength))
    {
        int index = Xlength;
    X.insert(index,0x40);

   // sizeBlock = 1536-4*l;

    sizeInform = Xlength*8+8;
    int ost = sizeInform%sizeBlock;



  //  char T0 = 0x00;
    if (ost!=0)
    {
        int t = sizeBlock-ost;
    for(int i = 8; i<=t;i = i+8)
    {
        index++;
        //int index = Xlength;

        X.insert(index,T0);
    }
}
  }
    SizeFile = SizeFile - uint64_t(Xlength);
    //step 2
    Xlength = X.length();
    int n = Xlength*8/sizeBlock;
    int sizeXi = sizeBlock/8;
 //   QByteArray Xi[n];

 //for (int i =0;i<192;i++)
 //{
     //  S.insert(i,T0);
   /*  if (i==184)
     {
          S.insert(184,Ls);
     }
     else
     {
         S.insert(i,T0);
     }

 }*/
// S.insert(184,Ls);
 /*for (int i = 185;i<192;i++)
 {
     S.insert(i,T0);

 }*/
    for (int i =0;i<n;i++)
    {
       for (int j =0 ; j<sizeXi;j++)
       {
           //Xi[i].insert(j,X.at(j+(i*sizeXi)));
           Xi[j] = X.at(j+(i*sizeXi));
       }
    //}
    //step 3

    //step 4
  //  for (int i=1 ; i<=n;i++)
   // {
      S = Lo(Xi/*[i-1]*/,S,sizeXi);
      S = BashF(S);
    }



  /*  for (int i = 0 ;i<32;i++)
    {
        Y.insert(i,S[i]);

    }*/

    //return Y;
}
QByteArray Cbash::BashResult()
{
    Y = Lo(S,Y,2*l/8);
    return Y;
}
QByteArray Cbash::BashF(QByteArray S)
{

    uint64_t C = 0xB194bac80a08f53b;
    for(int i =1 ;i<=24;i++)
    {
        quint64 Si[24];
        for (int i = 0; i<24; i++)
        {
    Si[i] = uint64_t(S.at(8*i))<<8;
    Si[i] = Si[i]^uint8_t(S.at(1+8*i));
    Si[i]= Si[i]<<8;
    Si[i] = Si[i]^uint8_t(S.at(2+8*i));
    Si[i]= Si[i]<<8;
    Si[i] = Si[i]^uint8_t(S.at(3+8*i));
    Si[i]= Si[i]<<8;
    Si[i] = Si[i]^uint8_t(S.at(4+8*i));
    Si[i]= Si[i]<<8;
    Si[i] = Si[i]^uint8_t(S.at(5+8*i));
    Si[i]= Si[i]<<8;
    Si[i] = Si[i]^uint8_t(S.at(6+8*i));
    Si[i]= Si[i]<<8;
    Si[i] = Si[i]^uint8_t(S.at(7+8*i));


        }





        uint m1,n1,m2,n2;
        m1 = 8;
        n1 = 53;
        m2 = 14;
        n2 = 1;
        for (int j=0;j<8;j++) {
          Octet64 s;
          s.w0 = Si[j];
          s.w1 = Si[8+j];
          s.w2 = Si[16+j];

                   s = Cbash::BashS(s,m1,n1,m2,n2);
                   Si[j] = s.w0;
                   Si[8+j]= s.w1;
                   Si[16+j]= s.w2;
                   m1 = (7*m1)%64;
                   n1 = (7*n1)%64;
                   m2 = (7*m2)%64;
                   n2 = (7*n2)%64;

        }

            QBuffer bufferS (&S);
            bufferS.open(QIODevice::WriteOnly);
            QDataStream ddS (&bufferS);
            Si[1] = Si[1]^C;
            ddS << Si[15]<<Si[10]<<Si[9]<<Si[12]<<Si[11]<<Si[14]<<Si[13]<<Si[8]<<
                   Si[17]<<Si[16]<<Si[19]<<Si[18]<<Si[21]<<Si[20]<<Si[23]<<Si[22]<<
                   Si[6]<<Si[3]<<Si[0]<<Si[5]<<Si[2]<<Si[7]<<Si[4]<<Si[1];

            if( ConvertSlov(C)%2 == 0)
            {
            C = Cbash::Shlo(C);
            }
            else
            {
                C = Cbash::Shlo(C);
                C = C^0xAED8E07F99E12BDC;
            }

    }
    return  S;

}
Octet64 Cbash::BashS(Octet64 w, uint m1, uint n1, uint m2, uint n2)
{
    uint64_t T0 = 0;
    uint64_t T1 = 0;
    uint64_t T2 = 0;
    T0 = RotHi(w.w0,m1);
    w.w0 = w.w0^w.w1;
    w.w0 = w.w0^w.w2;
    T1 = RotHi(w.w0,n1);
    T1 = T1^w.w1;
    w.w1 = T0^T1;
    w.w2 = w.w2^RotHi(w.w2,m2);
    w.w2 = w.w2^RotHi(T1,n2);
    T0 =~w.w2;
    T1 = w.w0|w.w2;
    T2 = w.w0&w.w1;
    T0 = T0|w.w1;
    w.w1 = w.w1^T1;
    w.w2 = w.w2^T2;
    w.w0 = w.w0^T0;
    return w;



}
uint64_t Cbash::Shlo(uint64_t c)
{
    uint64_t count = 1;
    c = Cbash::ConvertSlov(c);
    c = c>>count;
    c = Cbash::ConvertSlov(c);
    return  c;

}
uint64_t Cbash::SimvolNot(uint64_t w)
{
    w = Cbash::ConvertSlov(w);
    w = w^0xffffff;
    w = Cbash::ConvertSlov(w);
    return  w;
}
uint64_t Cbash::RotHi(uint64_t W0, uint m)
{
    W0 = Cbash::ConvertSlov(W0);
    uint64_t W1 =0;
    uint64_t W2 = 0;
    uint s = 64 - m;
    W1 = W0 << m;
    W2 = W0 >> s;
    W0 = W1^W2;

    return  W0 = Cbash::ConvertSlov(W0);

}
uint64_t Cbash::ConvertSlov(uint64_t s)
{
    uint64_t temp = s;
    uint8_t OctetSlov [8];
    for (int i = 0;i<8;i++)
    {
     OctetSlov[i] = uint8_t(s>>56);
     s = s<<8;
    }
    temp = uint64_t(OctetSlov[7])<<8;
    temp = temp^OctetSlov[6];
    temp = temp<<8;
    temp = temp^OctetSlov[5];
    temp = temp<<8;
    temp = temp^OctetSlov[4];
    temp = temp<<8;
    temp = temp^OctetSlov[3];
    temp = temp<<8;
    temp = temp^OctetSlov[2];
    temp = temp<<8;
    temp = temp^OctetSlov[1];
    temp = temp<<8;
    temp = temp^OctetSlov[0];
                 return temp;
}
QByteArray Cbash::Lo(QByteArray X, QByteArray S, int l)
{

for (int i = 0 ; i<l;i++)
{
    S[i] = X.at(i);
}
return S;
}
