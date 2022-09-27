#ifndef CBASH_H
#define CBASH_H
#include <coctet.h>


class Cbash
{
public:
    QByteArray Y;
    QByteArray S;
    int l;
    char Ls;
    char T0 = 0x00;
    int sizeBlock;
    int sizeInform;
    uint64_t SizeFile;

    Cbash( int L, uint64_t sizeFile);


    Octet64 BashS (Octet64 w, uint m1, uint n1, uint m2, uint n2);
    void  BashHash (QByteArray X);
    QByteArray BashResult();
    QByteArray BashF (QByteArray S);
     uint64_t RotHi (uint64_t W0, uint m);
     QByteArray Lo (QByteArray X, QByteArray S, int l);
     uint64_t ConvertSlov (uint64_t s);
     uint64_t SimvolNot (uint64_t w);
     uint64_t Shlo (uint64_t c);



};

#endif // CBASH_H
