#ifndef USER_H
#define USER_H

#include "utils.h"

void ProfilSaya(Akun *data, int jumlah, string namaLogin)
{
    system("cls");
    tampilkanLogoKecil();
    cout << "====================================================\n";
    cout << "||                👤 PROFIL SAYA 👤               ||\n";
    cout << "====================================================\n";
    try
    {
        int index = cariusername(data, jumlah, namaLogin);
        if (index == -1)
            throw invalid_argument("❌ Profil tidak ditemukan.");

        cout << "🆔 ID" << "      : " << data[index].id << "\n";
        cout << "👤 Nama" << "    : " << data[index].nama << "\n";
        cout << "🔑 Password" << ": " << data[index].pw << "\n";
        cout << "💰 Saldo" << "   : " << formatRupiah(data[index].saldo) << "\n";
        cout << "====================================================\n";

        cout << "\n🔧 Ingin mengubah password ?\n";
        cout << "   1. ✅ Ya, ganti password\n";
        cout << "   0. ❌ Tidak, kembali\n";

        int pilihan;
        bool validInput = false;
        while (!validInput)
        {
            try
            {
                pilihan = inputMenu("🎯 Pilihan (1/0): ");
                if (pilihan != 1 && pilihan != 0)
                    throw invalid_argument("❌ Pilihan harus 1 atau 0!\n");
                validInput = true;
            }
            catch (const exception &e)
            {
                cout << e.what() << "\n\n";
            }
        }

        if (pilihan == 1)
        {
            string pwBaru;
            bool passwordValid = false;
            while (!passwordValid)
            {
                try
                {
                    cout << "\n🔑 Masukkan password baru: ";
                    getline(cin, pwBaru);
                    validasiPassword(pwBaru);
                    passwordValid = true;
                }
                catch (const exception &e)
                {
                    cout << e.what() << " Silakan coba lagi.\n";
                }
            }

            data[index].pw = pwBaru;
            simpanAkun(data, jumlah);

            loadingAnimation();
            cout << "✅ Password berhasil diubah!\n\n";
        }
        else if (pilihan == 0)
        {
            cout << "🔙 Kembali ke menu utama...\n\n";
        }
        else
        {
            cout << "❌ Pilihan tidak valid!\n\n";
        }
    }
    catch (const exception &e)
    {
        cout << e.what() << "\n\n";
    }
}

void topUpSaldo(Akun *data, int jumlah, string namaLogin, TopUp *dataTopUp, int &jumlahTopUp, int maxTopUp)
{
    system("cls");
    tampilkanLogoKecil();
    cout << "====================================================\n";
    cout << "||               💳 TOP UP SALDO 💳               ||\n";
    cout << "====================================================\n";

    try
    {
        int index = cariusername(data, jumlah, namaLogin);
        if (index == -1)
            throw invalid_argument("❌ Akun tidak ditemukan!");

        cout << "💰 Saldo saat ini: " << formatRupiah(data[index].saldo) << endl;
        cout << "----------------------------------------------------\n";

        long long nominal = 0;
        string inputNominal;

        cout << "💵 Nominal top up: Rp ";
        getline(cin, inputNominal);
        if (inputNominal.empty())
            throw invalid_argument("❌ Input tidak boleh kosong!");
        for (char c : inputNominal)
            if (!isdigit(c))
                throw invalid_argument("❌ Input tidak valid!");

        if (inputNominal.length() > 10)
            throw invalid_argument("❌ Nominal terlalu besar!");

        nominal = stoll(inputNominal);
        if (nominal <= 0)
            throw invalid_argument("❌ Nominal harus lebih dari 0!");
        if (nominal > 2147483647)
            throw invalid_argument("❌ Nominal terlalu besar!");

        data[index].saldo += (int)nominal;

        if (jumlahTopUp < maxTopUp)
        {
            dataTopUp[jumlahTopUp].namaMember = namaLogin;
            dataTopUp[jumlahTopUp].nominal = (int)nominal;
            jumlahTopUp++;
        }

        loadingAnimation();
        cout << "✅ Top up berhasil!\n";
        cout << "💰 Saldo baru: " << formatRupiah(data[index].saldo) << endl
             << endl;
    }
    catch (const exception &e)
    {
        cout << endl
             << e.what() << "\n\n";
    }
}

void bookingKelas(Akun *data, int jumlahAkun, string namaLogin, Booking *dataBooking, int &jumlahBooking, int maxBooking, JadwalKelas *dataJadwal, int jumlahJadwal)
{
    system("cls");
    tampilkanLogoKecil();
    cout << "====================================================\n";
    cout << "||               📝 BOOKING KELAS 📝              ||\n";
    cout << "====================================================\n";

    try
    {
        validasiKapasitas(jumlahBooking, maxBooking);

        int indexMember = cariusername(data, jumlahAkun, namaLogin);
        if (indexMember == -1)
            throw invalid_argument("❌ Akun tidak ditemukan!");
        if (jumlahJadwal == 0)
            throw invalid_argument("❌ Belum ada jadwal kelas tersedia.");

        cout << "💰 Saldo Anda: " << formatRupiah(data[indexMember].saldo) << endl;
        tampilkanDaftarJadwal(dataJadwal, jumlahJadwal);

        int jadwalID = inputInteger("\n🆔 Masukkan ID Jadwal yang ingin dibooking: ");
        int indexJadwal = -1;
        for (int i = 0; i < jumlahJadwal; i++)
        {
            if (dataJadwal[i].jadwalID == jadwalID)
            {
                indexJadwal = i;
                break;
            }
        }

        if (indexJadwal == -1)
            throw invalid_argument("❌ ID Jadwal tidak ditemukan!");

        if (dataJadwal[indexJadwal].terisi >= dataJadwal[indexJadwal].kapasitas)
            throw invalid_argument("⚠️ Kelas sudah penuh!");

        for (int i = 0; i < jumlahBooking; i++)
        {
            if (dataBooking[i].namaMember == namaLogin &&
                dataBooking[i].jadwalID == jadwalID &&
                (dataBooking[i].status == "pending" || dataBooking[i].status == "approved"))
            {
                throw invalid_argument("⚠️ Anda sudah memiliki booking untuk jadwal ini!");
            }
        }

        int harga = dataJadwal[indexJadwal].harga;

        if (data[indexMember].saldo < harga)
            throw invalid_argument("❌ Saldo tidak cukup! Silakan top up terlebih dahulu.");

        int newBookingID = 1;
        for (int i = 0; i < jumlahBooking; i++)
            if (dataBooking[i].bookingID >= newBookingID)
                newBookingID = dataBooking[i].bookingID + 1;

        data[indexMember].saldo -= harga;
        dataBooking[jumlahBooking].bookingID = newBookingID;
        dataBooking[jumlahBooking].namaMember = namaLogin;
        dataBooking[jumlahBooking].memberID = data[indexMember].id;
        dataBooking[jumlahBooking].jadwalID = jadwalID;
        dataBooking[jumlahBooking].jenisKelas = dataJadwal[indexJadwal].jenisKelas + " - " + dataJadwal[indexJadwal].kategori;
        dataBooking[jumlahBooking].harga = harga;
        dataBooking[jumlahBooking].status = "pending";
        jumlahBooking++;
        dataJadwal[indexJadwal].terisi++;

        loadingAnimation();
        cout << "✅ Booking berhasil dibuat!\n\n";
        cout << "=============================================\n";
        cout << "||           📋 DETAIL BOOKING 📋          ||\n";
        cout << "=============================================\n\n";
        cout << "🆔 ID Booking   : " << newBookingID << endl;
        cout << "📅 Jadwal       : " << dataJadwal[indexJadwal].hari << ", " << dataJadwal[indexJadwal].jam << endl;
        cout << "🧘 Kelas        : " << dataJadwal[indexJadwal].jenisKelas << " (" << dataJadwal[indexJadwal].kategori << ")" << endl;
        cout << "👨‍🏫 Instruktur   : " << dataJadwal[indexJadwal].instruktur << endl;
        cout << "💰 Harga        : " << formatRupiah(harga) << endl;
        cout << "⏳ Status       : Menunggu Approval Admin" << endl;
        cout << "💵 Saldo Tersisa: " << formatRupiah(data[indexMember].saldo) << endl;
        cout << "=============================================\n\n";
    }
    catch (const exception &e)
    {
        cout << endl
             << e.what() << "\n\n";
    }
}

void batalkanBooking(Booking *dataBooking, string namaLogin, int &jumlahBooking, Akun *dataAkun, int jumlahAkun)
{
    system("cls");
    tampilkanLogoKecil();
    cout << "==============================================================\n";
    cout << "||                ❌ BATALKAN BOOKING KELAS ❌              ||\n";
    cout << "==============================================================\n";

    try
    {
        cout << left << setw(15) << "ID Booking " << setw(20) << "Kelas" << setw(15) << "Harga" << "Status" << endl;
        cout << "--------------------------------------------------------------\n";

        bool adaPending = false;
        for (int i = 0; i < jumlahBooking; i++)
        {
            if (dataBooking[i].namaMember == namaLogin && dataBooking[i].status == "pending")
            {
                adaPending = true;
                cout << left << setw(12) << dataBooking[i].bookingID
                     << setw(20) << dataBooking[i].jenisKelas
                     << setw(20) << "💰 " + formatRupiah(dataBooking[i].harga)
                     << "⏳ " << dataBooking[i].status << endl;
            }
        }

        if (!adaPending)
        {
            cout << "--------------------------------------------------------------\n";
            throw invalid_argument("❌ Tidak ada booking pending!");
        }
        cout << "==============================================================\n";

        int bookingID = inputInteger("\n🆔 Masukkan Booking ID yang ingin dibatalkan: ");
        int index = -1;
        for (int i = 0; i < jumlahBooking; i++)
        {
            if (dataBooking[i].bookingID == bookingID &&
                dataBooking[i].namaMember == namaLogin &&
                dataBooking[i].status == "pending")
            {
                index = i;
                break;
            }
        }

        if (index == -1)
            throw invalid_argument("❌ Booking tidak ditemukan!");

        cout << "=============================================\n";
        cout << "||           📋 DETAIL BOOKING 📋          ||\n";
        cout << "=============================================\n\n";
        cout << "🆔 Booking ID  : " << dataBooking[index].bookingID << endl;
        cout << "🧘 Kelas       : " << dataBooking[index].jenisKelas << endl;
        cout << "💰 Harga       : " << formatRupiah(dataBooking[index].harga) << endl;
        cout << "⏳ Status      : " << dataBooking[index].status << endl;
        cout << "---------------------------------------------\n";

        dataBooking[index].status = "canceled";
        int indexMember = cariusername(dataAkun, jumlahAkun, namaLogin);
        if (indexMember != -1)
        {
            dataAkun[indexMember].saldo += dataBooking[index].harga;
            cout << "\n✅ Booking berhasil dibatalkan! 💰 Saldo dikembalikan.\n";
        }
    }
    catch (const exception &e)
    {
        cout << endl
             << e.what() << "\n\n";
    }
}

void riwayatTransaksi(Booking *dataBooking, int jumlahBooking, TopUp *dataTopUp, int jumlahTopUp, string namaLogin)
{
    system("cls");
    tampilkanLogoKecil();
    cout << "======================================================================================\n";
    cout << "||                               📜 RIWAYAT TRANSAKSI 📜                            ||\n";
    cout << "======================================================================================\n";
    cout << left << setw(20) << "Jenis Transaksi " << setw(35) << "Keterangan " << setw(20) << "Nominal " << setw(10) << "Status " << endl;
    cout << "======================================================================================\n";

    bool AdaData = false;
    for (int i = 0; i < jumlahTopUp; i++)
    {
        if (dataTopUp[i].namaMember == namaLogin)
        {
            AdaData = true;
            cout << left << setw(20) << "💳 Top Up" << setw(35) << "Saldo ditambah"
                 << setw(20) << "➕ " + formatRupiah(dataTopUp[i].nominal)
                 << setw(10) << "✅ Berhasil" << endl;
        }
    }

    for (int i = 0; i < jumlahBooking; i++)
    {
        if (dataBooking[i].namaMember == namaLogin)
        {
            AdaData = true;
            string keterangan = "Booking " + dataBooking[i].jenisKelas;

            string nominal;
            if (dataBooking[i].status == "approved" || dataBooking[i].status == "pending")
                nominal = "➖ " + formatRupiah(dataBooking[i].harga);
            else
                nominal = "➕ " + formatRupiah(dataBooking[i].harga);

            string status;
            if (dataBooking[i].status == "approved")
                status = "✅ Approved";
            else if (dataBooking[i].status == "pending")
                status = "⏳ Pending";
            else if (dataBooking[i].status == "canceled")
                status = "❌ Canceled";
            else
                status = "❌ Rejected";

            cout << left << setw(20) << "📝 Booking" << setw(35) << keterangan
                 << setw(20) << nominal << setw(10) << status << endl;
        }
    }

    if (!AdaData)
        cout << "❌ Belum ada riwayat transaksi.\n";
    cout << "======================================================================================\n";
}

#endif