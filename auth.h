#ifndef AUTH_H
#define AUTH_H

#include "utils.h"

void login(Akun *data, int jumlah, bool &statusLogin, string &namaLogin, string &roleLogin)
{
    system("cls");
    tampilkanLogoKecil();
    cout << "====================================================\n";
    cout << "||              🔐 LOGIN SYSTEM 🔐                ||\n";
    cout << "====================================================\n";
    string inputNama, inputpw;
    int kesempatan = 3;

    while (kesempatan > 0)
    {
        try
        {
            bool usernameValid = false;
            while (!usernameValid)
            {
                try
                {
                    cout << "👤 Masukkan Username : ";
                    getline(cin, inputNama);
                    validasiHurufSpasi(inputNama, "Username", 4);
                    usernameValid = true;
                }
                catch (const exception &e)
                {
                    cout << e.what() << "\n";
                }
            }

            cout << "🔑 Masukkan Password : ";
            getline(cin, inputpw);
            validasiPassword(inputpw);

            int index = cariusername(data, jumlah, inputNama);
            if (index != -1 && data[index].pw == inputpw)
            {
                statusLogin = true;
                namaLogin = data[index].nama;
                roleLogin = data[index].role;

                loadingAnimation();
                cout << "✅ Login berhasil!\n";
                cout << "👋 Selamat datang, " << namaLogin << " (" << roleLogin << ")!\n";
                system("pause");
                return;
            }
            else
            {
                kesempatan--;
                cout << "\n❌ Login Gagal! Username atau Password salah.\n";
                if (kesempatan > 0)
                    cout << "⚠️   Sisa kesempatan: " << kesempatan << "\n\n";
                else
                {
                    cout << "🚫 Kesempatan Anda Habis!\n";
                    countdown(5);
                    system("pause");
                }
            }
        }
        catch (const exception &e)
        {
            cout << endl
                 << e.what() << "\n";
            kesempatan--;
            if (kesempatan > 0)
                cout << "⚠️   Sisa kesempatan: " << kesempatan << "\n\n";
            else
            {
                cout << "🚫 Kesempatan Habis.\n";
                countdown(5);
                system("pause");
            }
        }
    }
}

void registrasi(Akun *data, int &jumlah, int maxKapasitas)
{
    system("cls");
    tampilkanLogoKecil();
    cout << "====================================================\n";
    cout << "||        📝 REGISTRASI AKUN BARU 📝              ||\n";
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

        namaValid = true;
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

#endif