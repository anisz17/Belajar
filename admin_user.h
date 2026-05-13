#ifndef ADMIN_USER_H
#define ADMIN_USER_H

#include "utils.h"

void tambahMember(Akun *data, int &jumlah, int maxKapasitas)
{
    system("cls");
    tampilkanLogoKecil();
    cout << "====================================================\n";
    cout << "||           ➕ TAMBAH MEMBER BARU ➕             ||\n";
    cout << "====================================================\n";
    try
    {
        validasiKapasitas(jumlah, maxKapasitas);
        string namaBaru, pwBaru;
        bool namaValid = false;
        cout << "👤 Masukkan Nama Member : ";
        getline(cin, namaBaru);
        trimSpasi(namaBaru);
        validasiHurufSpasi(namaBaru, "Nama Member", 4);

        if (cariusername(data, jumlah, namaBaru) != -1)
            throw invalid_argument("❌ Username sudah terdaftar.");

        cout << "✅ Username valid!\n\n";

        bool passwordValid = false;
        while (!passwordValid)
        {
            try
            {
                cout << "🔑 Masukkan Password Member : ";
                getline(cin, pwBaru);
                validasiPassword(pwBaru);
                passwordValid = true;
                cout << "✅ Password valid!\n\n";
            }
            catch (const exception &e)
            {
                cout << e.what() << "\n";
                cout << "🔄 Silakan masukkan password kembali.\n\n";
            }
        }

        int newID = 1;
        for (int i = 0; i < jumlah; i++)
            if (data[i].role == "member" && data[i].id >= newID)
                newID = data[i].id + 1;

        data[jumlah].nama = namaBaru;
        data[jumlah].pw = pwBaru;
        data[jumlah].role = "member";
        data[jumlah].id = newID;
        data[jumlah].saldo = 0;
        jumlah++;

        simpanAkun(data, jumlah);

        loadingAnimation();
        cout << "✅ Member Berhasil Ditambahkan!\n";
        cout << "🆔 ID Member: " << newID << "\n\n";
    }
    catch (const exception &e)
    {
        cout << endl
             << e.what() << "\n\n";
    }
}

void lihatMember(Akun *data, int jumlah)
{
    system("cls");
    tampilkanLogoKecil();
    cout << "=====================================================\n";
    cout << "||             👀 LIHAT DATA MEMBER 👀             ||\n";
    cout << "=====================================================\n";

    try
    {
        Akun temp[20];
        int memberCount = 0;
        for (int i = 0; i < jumlah; i++)
            if (data[i].role == "member")
                temp[memberCount++] = data[i];

        for (int i = 0; i < memberCount - 1; i++)
        {
            int minIndex = i;
            for (int j = i + 1; j < memberCount; j++)
                if (temp[j].nama < temp[minIndex].nama)
                    minIndex = j;
            if (minIndex != i)
                swap(temp[i], temp[minIndex]);
        }

        cout << "\n====================================================\n";
        cout << "||               📋 DAFTAR MEMBER 📋              ||\n";
        cout << "====================================================\n";
        cout << left << setw(8) << "ID" << setw(20) << "Nama" << setw(20) << "Saldo" << endl;
        cout << "----------------------------------------------------\n";

        if (memberCount == 0)
            throw invalid_argument("❌ Belum ada data member.");
        else
            for (int i = 0; i < memberCount; i++)
                cout << left << setw(8) << temp[i].id
                     << setw(20) << temp[i].nama
                     << setw(20) << "💰 " + formatRupiah(temp[i].saldo) << "\n";

        cout << "====================================================\n\n";
    }
    catch (const exception &e)
    {
        cout << endl
             << e.what() << "\n\n";
    }
    system("pause");
}

void lihatMember(Akun *data, int jumlah, bool denganPencarian)
{
    system("cls");
    tampilkanLogoKecil();
    cout << "=====================================================\n";
    cout << "||             👀 LIHAT DATA MEMBER 👀             ||\n";
    cout << "=====================================================\n";

    Akun temp[20];
    int memberCount = 0;
    for (int i = 0; i < jumlah; i++)
        if (data[i].role == "member")
            temp[memberCount++] = data[i];

    for (int i = 0; i < memberCount - 1; i++)
    {
        int minIndex = i;
        for (int j = i + 1; j < memberCount; j++)
            if (temp[j].nama < temp[minIndex].nama)
                minIndex = j;
        if (minIndex != i)
            swap(temp[i], temp[minIndex]);
    }

    cout << "\n====================================================\n";
    cout << "||               📋 DAFTAR MEMBER 📋              ||\n";
    cout << "====================================================\n";
    cout << left << setw(8) << "ID" << setw(20) << "Nama" << setw(20) << "Saldo" << endl;
    cout << "----------------------------------------------------\n";

    if (memberCount == 0)
        cout << "❌ Belum ada data member.\n";
    else
        for (int i = 0; i < memberCount; i++)
            cout << left << setw(8) << temp[i].id
                 << setw(20) << temp[i].nama
                 << setw(20) << "💰 " + formatRupiah(temp[i].saldo) << "\n";

    cout << "====================================================\n\n";

    cout << "🔍 Ingin mencari member berdasarkan ID?\n";
    cout << "   1. ✅ Ya, cari member\n";
    cout << "   0. ⬅️ Kembali\n";
    cout << "----------------------------------------------------\n";

    try
    {
        int pilihan = inputMenu(" 🎯 Pilihan (1/0): ");

        if (pilihan == 1)
        {
            system("cls");
            tampilkanLogoKecil();
            cout << "====================================================\n";
            cout << "||        🔎 CARI MEMBER BERDASARKAN ID 🔎        ||\n";
            cout << "====================================================\n";

            tampilkanDaftarMember(data, jumlah);

            int targetID;
            targetID = inputInteger("\n🆔 Masukkan ID yang dicari: ");
            validasiID(targetID);
            cout << "\n🎯 Target ID: " << targetID << endl;
            cout << "--------------------------------------------\n";

            int hasil = -1, jumlahCek = 0;
            for (int i = 0; i < jumlah && hasil == -1; i++)
            {
                if (data[i].role == "member")
                {
                    jumlahCek++;
                    cout << "🔍 Cek member ke-" << jumlahCek << ": ID " << data[i].id;
                    if (data[i].id == targetID)
                    {
                        cout << " >>> ✅ COCOK!\n";
                        hasil = i;
                    }
                    else
                        cout << " (❌ tidak cocok)\n";
                }
            }
            cout << "--------------------------------------------\n";

            if (hasil != -1)
            {
                cout << "🎉 Ditemukan setelah " << jumlahCek << " pengecekan!\n\n";
                cout << "=============================================\n";
                cout << "||         ✅ MEMBER DITEMUKAN! ✅         ||\n";
                cout << "=============================================\n";
                cout << "🆔 ID       : " << data[hasil].id << endl;
                cout << "👤 Nama     : " << data[hasil].nama << endl;
                cout << "💰 Saldo    : " << formatRupiah(data[hasil].saldo) << endl;
                cout << "=============================================\n";
            }
            else
                cout << "❌ Member dengan ID " << targetID << " tidak ditemukan!\n";

            cout << "\n";
            system("pause");
        }
        else if (pilihan == 0)
        {
            return;
        }
        else
        {
            cout << "\n❌ Pilihan tidak valid!\n";
            system("pause");
        }
    }
    catch (const exception &e)
    {
        cout << endl
             << e.what() << "\n\n";
        system("pause");
    }
}

void hapusMember(Akun *data, int &jumlah)
{
    system("cls");
    tampilkanLogoKecil();
    cout << "====================================================\n";
    cout << "||               🗑️ HAPUS MEMBER 🗑️               ||\n";
    cout << "====================================================\n";
    tampilkanDaftarMember(data, jumlah);

    try
    {
        int IDHapus = inputInteger("\n🆔 Masukkan ID member yang ingin dihapus: ");
        validasiID(IDHapus);

        int index = cariID(data, jumlah, IDHapus);
        if (index == -1)
            throw invalid_argument("❌ Member dengan ID tersebut tidak ditemukan!");

        cout << "\n🗑️   Menghapus member: " << data[index].nama << "\n";

        for (int j = index; j < jumlah - 1; j++)
            data[j] = data[j + 1];
        jumlah--;

        simpanAkun(data, jumlah);

        loadingAnimation();
        cout << "✅ Data member berhasil dihapus!\n\n";
    }
    catch (const exception &e)
    {
        cout << endl
             << e.what() << "\n\n";
    }
}

#endif