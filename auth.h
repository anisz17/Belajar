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
    cin.ignore(1000, '\n');

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
                    cout << endl
                         << e.what() << "\n";
                }
            }

            cout << "🔑 Masukkan Password : ";
            getline(cin, inputpw);
            validasiPassword(inputpw);
            cin.ignore(1000, '\n');
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
                {
                    cout << "⚠️   Sisa kesempatan: " << kesempatan << "\n";
                }
                else
                {
                    cout << "\n🚫 Kesempatan Anda Habis!\n";
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
    cin.ignore(1000, '\n');
    try
    {
        validasiKapasitas(jumlah, maxKapasitas);
        string namaBaru, pwBaru;

        cout << "👤 Masukkan Username : ";
        getline(cin, namaBaru);

        validasiHurufSpasi(namaBaru, "Username", 4);

        if (cariusername(data, jumlah, namaBaru) != -1)
            throw runtime_error("❌ Username sudah terdaftar. Gunakan username lain.");

        cout << "🔑 Masukkan Password : ";
        getline(cin, pwBaru);
        validasiPassword(pwBaru);
        cout << endl;
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
        cout << "✅ Registrasi Berhasil! Silakan Login.\n";
        cout << "🆔 ID Anda: " << newID << "\n";
    }
    catch (const exception &e)
    {
        cout << endl
             << e.what() << "\n\n\n";
    }
}

#endif