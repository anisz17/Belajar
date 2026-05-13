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
#include <vector>
using namespace std;

bool adaDiDaftar(string input, vector<string> daftar)
{
    for (int i = 0; i < daftar.size(); i++)
    {
        if (input == daftar[i])
        {
            return true;
        }
    }
    return false;
}

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
        cout << i << "..";
        cout.flush();
        Sleep(1000);
    }
    cout << "\n\n";
    setColor(7);
}

void trimSpasi(string &teks)
{
    while (!teks.empty() && teks[0] == ' ')
        teks.erase(0, 1);
    while (!teks.empty() && teks[teks.length() - 1] == ' ')
        teks.erase(teks.length() - 1, 1);
}

int inputMenu(const string &prompt)
{
    string input;
    cout << prompt;
    getline(cin, input);

    if (input.empty())
        throw invalid_argument("❌ Input tidak boleh kosong!");
    for (char c : input)
    {
        if (!isdigit(c))
            throw invalid_argument("❌ Input tidak valid!\n");
    }

    return stoi(input);
}

int inputInteger(const string &prompt)
{
    string input;
    cout << prompt;
    getline(cin, input);

    if (input.empty())
        throw invalid_argument("❌ Input tidak boleh kosong!");
    for (char c : input)
    {
        if (!isdigit(c))
            throw invalid_argument("❌ Input tidak valid!\n");
    }
    int nilai = stoi(input);
    if (nilai <= 0)
        throw invalid_argument("❌ Input tidak valid!");

    return nilai;
}

bool inputYesNo(const string &prompt)
{
    string input;
    while (true)
    {
        cout << prompt;
        if (cin.peek() == '\n')
            cin.ignore(1000, '\n');
        getline(cin, input);

        if (input.empty())
        {
            cout << "❌ Masukkan y atau n!\n";
            continue;
        }
        char jawaban = tolower(input[0]);
        if (jawaban == 'y')
            return true;
        if (jawaban == 'n')
            return false;

        cout << "❌ Masukkan y atau n!\n";
    }
}

void validasiKapasitas(int jumlah, int maxKapasitas)
{
    if (jumlah >= maxKapasitas)
        throw invalid_argument("⚠️ Kapasitas penuh!");
}

void validasiID(int id)
{
    if (id <= 0)
        throw invalid_argument("❌ ID tidak valid!");
}

void validasiHurufSpasi(const string &teks, const string &namaField, int minLen = 0)
{
    if (teks.empty())
        throw invalid_argument("❌ input tidak boleh kosong!\n");

    if ((int)teks.length() < minLen)
        throw invalid_argument("❌ input minimal 4 karakter!");

    for (char c : teks)
    {
        if (!isalpha((unsigned char)c) && c != ' ')
            throw invalid_argument("❌ input hanya boleh huruf dan spasi!");
    }
}

vector<string> daftarHari = {
    "Senin", "Selasa", "Rabu", "Kamis", "Jumat", "Sabtu", "Minggu"};
string pilihHari()
{
    cout << "\n📅 Pilih Hari:\n";
    for (int i = 0; i < daftarHari.size(); i++)
        cout << i + 1 << ". " << daftarHari[i] << endl;

    string pilihan;
    cout << "Pilih: ";
    getline(cin, pilihan);
    if (pilihan.empty())
        throw invalid_argument("\n❌ Input tidak boleh kosong!");
    for (char c : pilihan)
    {
        if (!isdigit(c))
            throw invalid_argument("\n❌ Input tidak valid!");
    }
    int pilih = stoi(pilihan);

    if (pilih < 1 || pilih > daftarHari.size())
        throw invalid_argument("\n❌ Pilihan tidak valid!");

    return daftarHari[pilih - 1];
}

void validasiFormatJam(string jam)
{
    if (jam.empty())
        throw invalid_argument("❌ Jam tidak boleh kosong!");
    if (jam.length() != 5 || jam[2] != ':')
        throw invalid_argument("❌ Format HH:MM");

    int h = stoi(jam.substr(0, 2));
    int m = stoi(jam.substr(3, 2));

    if (h < 0 || h > 23 || m < 0 || m > 59)
        throw invalid_argument("❌ Jam tidak valid");
}

void validasiRentangJam(string mulai, string selesai)
{
    int m1 = stoi(mulai.substr(0, 2)) * 60 + stoi(mulai.substr(3, 2));
    int m2 = stoi(selesai.substr(0, 2)) * 60 + stoi(selesai.substr(3, 2));

    if (m2 <= m1)
        throw invalid_argument("❌ Jam selesai harus lebih besar");
}

string inputJam()
{
    string mulai, selesai;

    while (true)
    {
        try
        {
            cout << "\n🕐 Jam Mulai: ";
            getline(cin, mulai);
            cout << "🕐 Jam Selesai: ";
            getline(cin, selesai);

            if (mulai.empty() || selesai.empty())
                throw invalid_argument("❌ Jam tidak boleh kosong");

            validasiFormatJam(mulai);
            validasiFormatJam(selesai);
            validasiRentangJam(mulai, selesai);

            return mulai + " - " + selesai;
        }
        catch (exception &e)
        {
            cout << e.what() << "\n\n";
        }
    }
}

void validasiJenis(string jenis)
{
    vector<string> daftarJenis = {
        "mat",
        "reformer",
        "cadillac",
        "klinis",
        "kontemporer"};
    if (jenis.empty())
        throw invalid_argument("❌ Jenis kelas tidak boleh kosong!");
    if (!adaDiDaftar(jenis, daftarJenis))
    {
        throw invalid_argument(
            "❌ Jenis kelas tidak valid!");
    }
}

void validasiKategori(string kategori)
{
    vector<string> daftarKategori = {
        "private",
        "reguler"};
    if (kategori.empty())
        throw invalid_argument("❌ Kategori tidak boleh kosong!");
    if (!adaDiDaftar(kategori, daftarKategori))
    {
        throw invalid_argument(
            "❌ Kategori tidak valid! "
            "Pilih: Private/Reguler");
    }
}

void validasiPassword(const string &pw)
{
    if (pw.empty())
        throw invalid_argument("❌ Password tidak boleh kosong!");
    if ((int)pw.length() < 3)
        throw invalid_argument("❌ Password minimal 3 karakter!");
}

string formatRupiah(int harga)
{
    return "Rp " + to_string(harga);
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
    cout << "\n====================================================\n";
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
            cout << left << setw(8) << data[i].id
                 << setw(20) << data[i].nama
                 << setw(20) << "💰 " + formatRupiah(data[i].saldo) << "\n";
        }
    }
    if (!ada)
        cout << "❌ Belum ada data member terdaftar !\n";
    cout << "====================================================\n";
}

void tampilkanDaftarJadwal(JadwalKelas *dataJadwal, int jumlahJadwal)
{
    cout << "\n==========================================================================================================\n";
    cout << "||                                     📅 DAFTAR JADWAL KELAS 📅                                        ||\n";
    cout << "==========================================================================================================\n";
    cout << left << setw(5) << "ID" << setw(10) << "Hari" << setw(15) << "Jam"
         << setw(18) << "Jenis" << setw(15) << "Kategori" << setw(15) << "Instruktur"
         << setw(12) << "Harga" << "Kapasitas" << endl;
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
            cout << left << setw(5) << dataJadwal[i].jadwalID
                 << setw(10) << dataJadwal[i].hari
                 << setw(15) << dataJadwal[i].jam
                 << setw(18) << dataJadwal[i].jenisKelas
                 << setw(15) << dataJadwal[i].kategori
                 << setw(15) << dataJadwal[i].instruktur
                 << setw(12) << formatRupiah(dataJadwal[i].harga)
                 << dataJadwal[i].terisi << "/" << dataJadwal[i].kapasitas
                 << " (sisa " << sisa << ")" << endl;
        }
    }
    cout << "==========================================================================================================\n";
}

#endif