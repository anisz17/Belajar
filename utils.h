#ifndef UTILS_H
#define UTILS_H

#include "struct.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <windows.h>
#include <cctype>
#include <fstream>
using namespace std;

void setColor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void tampilkanLogoKecil()
{
    cout << "\n";
    cout << "====================================================\n";
    cout << "||           💪 STUDIO PILATES MANIAK 💪          ||\n";
    cout << "====================================================\n";
}

void loadingAnimation()
{
    setColor(14);
    cout << "\n⏳ Loading";
    for (int i = 0; i < 5; i++)
    {
        Sleep(200);
        cout << ".";
        cout.flush();
    }
    cout << "\n";
    setColor(7);
}

void countdown(int detik)
{
    setColor(12);
    cout << "\n❌ Terlalu banyak percobaan gagal!\n";
    setColor(14);
    cout << "⏰ Silakan tunggu ";
    for (int i = detik; i > 0; i--)
    {
        cout << i << "....";
        cout.flush();
        Sleep(1000);
    }
    cout << "\n\n";
    setColor(7);
}

int inputInteger(const string &prompt)
{
    int nilai;
    cout << prompt;
    cin >> nilai;
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(1000, '\n');
        throw invalid_argument("❌ Input Harus berupa angka.");
    }
    return nilai;
}

void validasiHurufSpasi(const string &teks, const string &namaField, int minLen = 0)
{
    if (teks.empty() || teks == " ")
        throw invalid_argument("❌ " + namaField + " tidak boleh kosong!");
    if ((int)teks.length() < minLen)
        throw invalid_argument("❌ " + namaField + " minimal " + to_string(minLen) + " karakter!");

    bool semuaSpasi = true;
    for (char c : teks)
    {
        if (!isalpha(c) && c != ' ')
            throw invalid_argument("❌ " + namaField + " hanya boleh huruf dan spasi!");
        if (c != ' ')
            semuaSpasi = false;
    }
    if (semuaSpasi)
        throw invalid_argument("❌ " + namaField + " tidak boleh hanya berisi spasi!");
}

void validasiHari(const string &hari)
{
    if (hari.empty())
        throw invalid_argument("❌ Hari tidak boleh kosong!");

    for (int i = 0; i < hari.length(); i++)
    {
        if (!isalpha(hari[i]) && hari[i] != ' ')
        {
            throw invalid_argument("❌ Hari hanya boleh berisi huruf!");
        }
    }
}

void validasiJam(const string &jam)
{
    if (jam.empty())
        throw invalid_argument("❌ Jam tidak boleh kosong!");

    for (int i = 0; i < jam.length(); i++)
    {
        if (!isdigit(jam[i]) && jam[i] != ':' && jam[i] != '-' && jam[i] != ' ')
        {
            throw invalid_argument("❌ Format jam tidak valid!");
        }
    }
}

void validasiPassword(const string &pw)
{
    if (pw.empty())
        throw invalid_argument("❌ Password tidak boleh kosong!");
    if ((int)pw.length() < 3)
        throw length_error("❌ Password terlalu pendek! Minimal 3 karakter.");
}

void validasiKapasitas(int jumlah, int maxKapasitas)
{
    if (jumlah >= maxKapasitas)
        throw length_error("⚠️ Kapasitas penuh! Tidak dapat menambah data.");
}

void validasiID(int id)
{
    if (id <= 0)
        throw out_of_range("❌ ID tidak valid! Harus berupa angka positif.");
}

string formatRupiah(int harga)
{
    stringstream ss;
    ss << "Rp " << harga;
    return ss.str();
}

void simpanAkun(Akun *data, int jumlah)
{
    ofstream file("akun.csv");
    file << "nama,pw,role,id,saldo\n";
    for (int i = 0; i < jumlah; i++)
    {
        file << data[i].nama << ","
             << data[i].pw << ","
             << data[i].role << ","
             << data[i].id << ","
             << data[i].saldo << "\n";
    }
    file.close();
}

void muatAkun(Akun *data, int &jumlah)
{
    ifstream file("akun.csv");
    if (!file.is_open())
    {
        data[0] = {"annisa", "078", "admin", 0, 0};
        data[1] = {"juun", "0412", "member", 1, 0};
        jumlah = 2;
        simpanAkun(data, jumlah);
        return;
    }

    string baris;
    getline(file, baris);
    jumlah = 0;

    while (getline(file, baris) && jumlah < 20)
    {
        stringstream ss(baris);
        string token;

        getline(ss, token, ',');
        data[jumlah].nama = token;
        getline(ss, token, ',');
        data[jumlah].pw = token;
        getline(ss, token, ',');
        data[jumlah].role = token;
        getline(ss, token, ',');
        data[jumlah].id = stoi(token);
        getline(ss, token, ',');
        data[jumlah].saldo = stoi(token);
        jumlah++;
    }
    file.close();
}

void simpanJadwal(JadwalKelas *data, int jumlah)
{
    ofstream file("jadwal.csv");
    file << "jadwalID,hari,jam,jenisKelas,kategori,instruktur,harga,kapasitas,terisi\n";
    for (int i = 0; i < jumlah; i++)
    {
        file << data[i].jadwalID << ","
             << data[i].hari << ","
             << data[i].jam << ","
             << data[i].jenisKelas << ","
             << data[i].kategori << ","
             << data[i].instruktur << ","
             << data[i].harga << ","
             << data[i].kapasitas << ","
             << data[i].terisi << "\n";
    }
    file.close();
}

void muatJadwal(JadwalKelas *data, int &jumlah)
{
    ifstream file("jadwal.csv");
    if (!file.is_open())
    {
        jumlah = 0;
        return;
    }

    string baris;
    getline(file, baris);
    jumlah = 0;

    while (getline(file, baris) && jumlah < 30)
    {
        stringstream ss(baris);
        string token;

        getline(ss, token, ',');
        data[jumlah].jadwalID = stoi(token);
        getline(ss, token, ',');
        data[jumlah].hari = token;
        getline(ss, token, ',');
        data[jumlah].jam = token;
        getline(ss, token, ',');
        data[jumlah].jenisKelas = token;
        getline(ss, token, ',');
        data[jumlah].kategori = token;
        getline(ss, token, ',');
        data[jumlah].instruktur = token;
        getline(ss, token, ',');
        data[jumlah].harga = stoi(token);
        getline(ss, token, ',');
        data[jumlah].kapasitas = stoi(token);
        getline(ss, token, ',');
        data[jumlah].terisi = stoi(token);
        jumlah++;
    }
    file.close();
}

int cariusername(Akun *data, int jumlah, string targetNama, int index = 0)
{
    if (index >= jumlah)
        return -1;
    if (data[index].nama == targetNama)
        return index;
    return cariusername(data, jumlah, targetNama, index + 1);
}

int cariID(Akun *data, int jumlah, int targetID)
{
    for (int i = 0; i < jumlah; i++)
        if (data[i].role == "member" && data[i].id == targetID)
            return i;
    return -1;
}

void tampilkanDaftarMember(Akun *data, int jumlah)
{
    cout << "\n";
    cout << "====================================================\n";
    cout << "||          👥 DAFTAR MEMBER TERDAFTAR 👥         ||\n";
    cout << "====================================================\n";

    cout << left << setw(8) << "ID" << setw(20) << "Nama" << setw(20) << "Saldo" << endl;
    cout << "----------------------------------------------------\n";

    bool ada = false;
    for (int i = 0; i < jumlah; i++)
    {
        if (data[i].role == "member")
        {
            ada = true;
            cout << left << setw(8) << data[i].id;
            cout << setw(20) << data[i].nama;
            cout << setw(20) << "💰 " + formatRupiah(data[i].saldo) << "\n";
        }
    }
    if (!ada)
    {
        cout << "❌ Belum ada data member terdaftar !\n";
    }
    cout << "====================================================\n";
}

void tampilkanDaftarJadwal(JadwalKelas *dataJadwal, int jumlahJadwal)
{
    cout << "\n";
    cout << "==========================================================================================================\n";
    cout << "||                                     📅 DAFTAR JADWAL KELAS 📅                                        ||\n";
    cout << "==========================================================================================================\n";

    cout << left
         << setw(5) << "ID"
         << setw(10) << "Hari"
         << setw(15) << "Jam"
         << setw(18) << "Jenis"
         << setw(15) << "Kategori"
         << setw(15) << "Instruktur"
         << setw(12) << "Harga"
         << "Kapasitas" << endl;
    cout << "----------------------------------------------------------------------------------------------------------\n";

    if (jumlahJadwal == 0)
    {
        cout << "❌ Belum ada data jadwal !\n";
    }
    else
    {
        for (int i = 0; i < jumlahJadwal; i++)
        {
            int sisa = dataJadwal[i].kapasitas - dataJadwal[i].terisi;

            cout << left << setw(5) << dataJadwal[i].jadwalID;
            cout << setw(10) << dataJadwal[i].hari;
            cout << setw(15) << dataJadwal[i].jam;
            cout << setw(18) << dataJadwal[i].jenisKelas;
            cout << setw(15) << dataJadwal[i].kategori;
            cout << setw(15) << dataJadwal[i].instruktur;
            cout << setw(12) << formatRupiah(dataJadwal[i].harga);
            cout << dataJadwal[i].terisi << "/" << dataJadwal[i].kapasitas
                 << " (sisa " << sisa << ")" << endl;
        }
    }

    cout << "==========================================================================================================\n";
}

#endif