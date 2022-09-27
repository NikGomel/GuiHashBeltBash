#ifndef COCTET_H
#define COCTET_H
#include <QByteArray>
#include<QString>

struct Octet
{
public:
    uint u1;
    uint u2;
    uint u3;
    uint u4;
    Octet static plus (Octet a, uint b);

};
struct Octet32
{
public:
     uint u1;
     uint u2;
     uint u3;
     uint u4;
     uint u5;
     uint u6;
     uint u7;
     uint u8;
     QByteArray static transformationByte (Octet32 a);
     uint static convert (uint x);

};
struct Octet64
{
public:
uint64_t w0;
uint64_t w1;
uint64_t w2;
};

#endif // COCTET_H
