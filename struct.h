#ifndef STRUCTS_H
#define STRUCTS_H

#include <string>
using namespace std;

struct Akun
{
    string nama;
    string pw;
    string role;
    int id;
    int saldo;
};

struct JadwalKelas
{
    int jadwalID;
    string hari;
    string jam;
    string jenisKelas;
    string kategori;
    string instruktur;
    int harga;
    int kapasitas;
    int terisi;
};

struct Booking
{
    int bookingID;
    string namaMember;
    int memberID;
    int jadwalID;
    string jenisKelas;
    int harga;
    string status;
};

struct TopUp
{
    string namaMember;
    int nominal;
};

#endif