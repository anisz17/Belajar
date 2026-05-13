#include <iostream>
#include <windows.h>
#include "struct.h"
#include "utils.h"
#include "auth.h"
#include "admin_user.h"
#include "admin_jadwal.h"
#include "user.h"
#include <csignal>

using namespace std;

void tanganiCtrlC(int signal)
{
    cout << "\n\n⚠️   Ctrl + C terdeteksi!\n";
    cout << "Program dihentikan.\n";
    ExitProcess(signal);
}

void setupErrorHandling()
{
    signal(SIGINT, tanganiCtrlC);
}

int main()
{
    setupErrorHandling();
    SetConsoleOutputCP(65001);

    const int MAX = 10;
    const int MAX_BOOKING = 50;
    const int MAX_JADWAL = 30;
    const int MAX_TOPUP = 100;

    Akun dataAkun[MAX];
    int jumlah = 0;

    Booking dataBooking[MAX_BOOKING];
    int jumlahBooking = 0;

    JadwalKelas dataJadwal[MAX_JADWAL];
    int jumlahJadwal = 0;

    TopUp dataTopUp[MAX_TOPUP];
    int jumlahTopUp = 0;

    muatAkun(dataAkun, jumlah);
    muatJadwal(dataJadwal, jumlahJadwal);

    if (jumlahJadwal == 0)
    {
        simpanJadwal(dataJadwal, jumlahJadwal);
    }

    Akun *ptrAkun = dataAkun;
    bool programAktif = true;
    bool statusLogin = false;
    string namaLogin = "";
    string roleLogin = "";

    while (programAktif)
    {
        if (!statusLogin)
        {
            system("cls");
            setColor(11);
            cout << "\n";
            cout << "================================================================\n";
            cout << "||                                                            ||\n";
            cout << "||     ######   ##  ##       ###   ######  #####  #####       ||\n";
            cout << "||     ##  ##   ##  ##      ## ##    ##    ##     ##          ||\n";
            cout << "||     #####    ##  ##      ######   ##    ####   ####        ||\n";
            cout << "||     ##       ##  ##      ##  ##   ##    ##        ##       ||\n";
            cout << "||     ##       ##  ### ##  ##  ##   ##    #####  ####        ||\n";
            cout << "||                                                            ||\n";
            cout << "||     ##   ##   ###   ##  ##   ##   ###   ##  ##             ||\n";
            cout << "||     ### ###  ## ##  ### ##   ##  ## ##  ## ##              ||\n";
            cout << "||     ## # ##  #####  ## ###   ##  #####  ####               ||\n";
            cout << "||     ##   ##  ## ##  ##  ##   ##  ## ##  ## ##              ||\n";
            cout << "||     ##   ##  ## ##  ##  ##   ##  ## ##  ##  ##             ||\n";
            cout << "||                                                            ||\n";
            cout << "================================================================\n";
            setColor(14);
            cout << "              💪 >> STUDIO PILATES MANAGEMENT << 💪\n";
            setColor(10);
            cout << "                   Your Health, Our Priority! \n";
            setColor(7);
            cout << endl;

            cout << "============================================\n";
            cout << "||             🏠 MENU UTAMA 🏠           ||\n";
            cout << "============================================\n";
            cout << "1. 🔒 Login\n";
            cout << "2. 📝 Register\n";
            cout << "0. ❌ Keluar\n";
            cout << "--------------------------------------------\n";

            try
            {
                string input;
                cout << "🎯 Pilih menu (1/2/0): ";
                getline(cin, input);

                if (input.empty())
                    throw invalid_argument("❌ Input tidak boleh kosong!\n");

                for (char c : input)
                {
                    if (!isdigit(c))
                        throw invalid_argument("❌ Input tidak valid!\n");
                }

                int pilihan = stoi(input);

                if (pilihan == 1)
                    login(ptrAkun, jumlah, statusLogin, namaLogin, roleLogin);
                else if (pilihan == 2)
                {
                    registrasi(ptrAkun, jumlah, MAX);
                    system("pause");
                }
                else if (pilihan == 0)
                {
                    loadingAnimation();
                    system("cls");
                    setColor(11);
                    cout << "\n";
                    cout << "    ================================================================\n";
                    cout << "    ||                                                            ||\n";
                    cout << "    ||         #####  #####  ####    ##   ##   ##   ###           ||\n";
                    cout << "    ||           ##   ##     ##  ##  ##   ### ###  ## ##          ||\n";
                    cout << "    ||           ##   ####   ####    ##   ## # ##  #####          ||\n";
                    cout << "    ||           ##   ##     ##  ##  ##   ##   ##  ## ##          ||\n";
                    cout << "    ||           ##   #####  ##  ##  ##   ##   ##  ## ##          ||\n";
                    cout << "    ||                                                            ||\n";
                    cout << "    ||             ##  ##   ###    ####   ##  ##  ##              ||\n";
                    cout << "    ||             ## ##   ## ##  ##      ##  ##  ##              ||\n";
                    cout << "    ||             ####    #####   ####   ##  ######              ||\n";
                    cout << "    ||             ## ##   ## ##      ##  ##  ##  ##              ||\n";
                    cout << "    ||             ##  ##  ## ##  ####    ##  ##  ##              ||\n";
                    cout << "    ||                                                            ||\n";
                    cout << "    ================================================================\n";
                    setColor(10);
                    cout << "                  💪 Stay Healthy, Stay Strong! 💪\n\n";
                    programAktif = false;
                }
                else
                    throw invalid_argument("❌ Pilihan tidak valid!");
            }
            catch (const exception &e)
            {
                cout << endl
                     << e.what() << "\n\n";
                system("pause");
            }
        }
        else
        {
            if (roleLogin == "admin")
            {
                system("cls");
                tampilkanLogoKecil();

                cout << "============================================\n";
                cout << "||            💼 MENU ADMIN 💼            ||\n";
                cout << "============================================\n";
                cout << "1. ➕ Tambah Member\n";
                cout << "2. 👀 Lihat Member\n";
                cout << "3. 🗑️  Hapus Member\n";
                cout << "4. ➕ Tambah Jadwal\n";
                cout << "5. 👀 Lihat Jadwal\n";
                cout << "6. ✏️  Update Jadwal\n";
                cout << "7. 🗑️  Hapus Jadwal\n";
                cout << "8. ✅ Approval Booking\n";
                cout << "0. 🚪 Logout\n";
                cout << "--------------------------------------------\n";

                try
                {
                    string input;
                    cout << "🎯 Pilih menu (0-8): ";
                    getline(cin, input);

                    if (input.empty())
                        throw invalid_argument("❌ Input tidak boleh kosong!");

                    for (char c : input)
                    {
                        if (!isdigit(c))
                            throw invalid_argument("❌ Input tidak valid!");
                    }

                    int pilihan = stoi(input);

                    if (pilihan == 1)
                    {
                        tambahMember(ptrAkun, jumlah, MAX);
                        system("pause");
                    }
                    else if (pilihan == 2)
                        lihatMember(ptrAkun, jumlah, true);
                    else if (pilihan == 3)
                    {
                        hapusMember(ptrAkun, jumlah);
                        system("pause");
                    }
                    else if (pilihan == 4)
                    {
                        tambahJadwal(dataJadwal, jumlahJadwal, MAX_JADWAL);
                        system("pause");
                    }
                    else if (pilihan == 5)
                    {
                        lihatJadwal(dataJadwal, jumlahJadwal);
                        system("pause");
                    }
                    else if (pilihan == 6)
                    {
                        updateJadwal(dataJadwal, jumlahJadwal);
                        system("pause");
                    }
                    else if (pilihan == 7)
                    {
                        hapusJadwal(dataJadwal, jumlahJadwal);
                        system("pause");
                    }
                    else if (pilihan == 8)
                    {
                        approvalBooking(dataBooking, jumlahBooking, ptrAkun, jumlah);
                        system("pause");
                    }
                    else if (pilihan == 0)
                    {
                        statusLogin = false;
                        namaLogin = "";
                        roleLogin = "";
                        loadingAnimation();
                        cout << "✅ Berhasil Logout!\n\n";
                        system("pause");
                    }
                    else
                        throw invalid_argument("❌ Pilihan tidak valid!");
                }
                catch (const exception &e)
                {
                    cout << endl
                         << e.what() << "\n\n";
                    system("pause");
                }
            }
            else if (roleLogin == "member")
            {
                system("cls");
                tampilkanLogoKecil();

                cout << "============================================\n";
                cout << "||        👤 MENU MEMBER 👤               ||\n";
                cout << "============================================\n";
                cout << "1. 👁️  Lihat Profil Saya\n";
                cout << "2. 💳 Top Up Saldo\n";
                cout << "3. 📝 Booking Kelas\n";
                cout << "4. ❌ Batalkan Booking Kelas\n";
                cout << "5. 📜 Riwayat Transaksi\n";
                cout << "0. 🚪 Logout\n";
                cout << "--------------------------------------------\n";

                try
                {
                    string input;
                    cout << "🎯 Pilih menu: ";
                    getline(cin, input);

                    if (input.empty())
                        throw invalid_argument("❌ Input tidak boleh kosong!");

                    for (char c : input)
                    {
                        if (!isdigit(c))
                            throw invalid_argument("❌ Input tidak valid!");
                    }

                    int pilihan = stoi(input);

                    if (pilihan == 1)
                    {
                        ProfilSaya(ptrAkun, jumlah, namaLogin);
                        system("pause");
                    }
                    else if (pilihan == 2)
                    {
                        topUpSaldo(ptrAkun, jumlah, namaLogin, dataTopUp, jumlahTopUp, MAX_TOPUP);
                        system("pause");
                    }
                    else if (pilihan == 3)
                    {
                        bookingKelas(ptrAkun, jumlah, namaLogin, dataBooking, jumlahBooking, MAX_BOOKING, dataJadwal, jumlahJadwal);
                        system("pause");
                    }
                    else if (pilihan == 4)
                    {
                        batalkanBooking(dataBooking, namaLogin, jumlahBooking, ptrAkun, jumlah);
                        system("pause");
                    }
                    else if (pilihan == 5)
                    {
                        riwayatTransaksi(dataBooking, jumlahBooking, dataTopUp, jumlahTopUp, namaLogin);
                        system("pause");
                    }
                    else if (pilihan == 0)
                    {
                        statusLogin = false;
                        namaLogin = "";
                        roleLogin = "";
                        loadingAnimation();
                        cout << "✅ Berhasil Logout!\n\n";
                        system("pause");
                    }
                    else
                        throw invalid_argument("❌ Pilihan tidak valid!");
                }
                catch (const exception &e)
                {
                    cout << endl
                         << e.what() << "\n\n";
                    system("pause");
                }
            }
        }
    }
    return 0;
}