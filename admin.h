#ifndef ADMIN_H
#define ADMIN_H

#include "utils.h"

void tambahMember(Akun *data, int &jumlah, int maxKapasitas)
{
    system("cls");
    tampilkanLogoKecil();
    cout << "====================================================\n";
    cout << "||           ➕ TAMBAH MEMBER BARU ➕             ||\n";
    cout << "====================================================\n";
    cin.ignore(1000, '\n');
    try
    {
        validasiKapasitas(jumlah, maxKapasitas);
        string namaBaru, pwBaru;
        cout << "👤 Masukkan Nama Member : ";
        getline(cin, namaBaru);

        validasiHurufSpasi(namaBaru, "Username", 4);

        if (cariusername(data, jumlah, namaBaru) != -1)
            throw runtime_error("❌ Username sudah terdaftar.");

        cout << "🔑 Masukkan Password Member : ";
        cin >> pwBaru;
        validasiPassword(pwBaru);

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
        int pilihan = inputInteger(" 🎯 Pilihan (1/0): ");

        if (pilihan == 1)
        {
            system("cls");
            tampilkanLogoKecil();
            cout << "====================================================\n";
            cout << "||        🔎 CARI MEMBER BERDASARKAN ID 🔎        ||\n";
            cout << "====================================================\n";

            tampilkanDaftarMember(data, jumlah);

            int targetID;
            while (true)
            {
                try
                {
                    targetID = inputInteger("\n🆔 Masukkan ID yang dicari: ");
                    validasiID(targetID);
                    break;
                }
                catch (const exception &e)
                {
                    cout << endl
                         << e.what() << " Silakan coba lagi.\n";
                }
            }

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
            throw runtime_error("❌ Member dengan ID tersebut tidak ditemukan!");
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

void tambahJadwal(JadwalKelas *dataJadwal, int &jumlahJadwal, int maxJadwal)
{
    system("cls");
    tampilkanLogoKecil();
    cout << "===========================================================\n";
    cout << "||               ➕ TAMBAH JADWAL KELAS ➕               ||\n";
    cout << "===========================================================\n";

    if (jumlahJadwal >= maxJadwal)
    {
        cout << "⚠️ Kuota penyimpanan jadwal penuh!\n\n";
        return;
    }

    try
    {
        cin.ignore(1000, '\n');

        string hariInput;
        cout << "\n📅 Hari (Senin/Selasa/Rabu/Kamis/Jumat/Sabtu/Minggu): ";
        getline(cin, hariInput);
        validasiHari(hariInput);

        string jamInput;
        cout << "🕐 Jam (contoh: 08:00 - 09:00): ";
        getline(cin, jamInput);
        validasiJam(jamInput);

        string jenisInput;
        cout << "🧘 Jenis Kelas (Mat/Reformer/Cadillac/Klinis/Kontemporer): ";
        getline(cin, jenisInput);
        validasiHurufSpasi(jenisInput, "Jenis kelas");

        string kategoriInput;
        cout << "📌 Kategori (Private/Reguler): ";
        getline(cin, kategoriInput);
        validasiHurufSpasi(kategoriInput, "Kategori");

        string instrukturInput;
        cout << "👩‍🦰👨‍🦰 Instruktur: ";
        getline(cin, instrukturInput);
        validasiHurufSpasi(instrukturInput, "Instruktur");

        int hargaInput;
        bool validHarga = false;
        while (!validHarga)
        {
            try
            {
                cout << "💰 Harga Kelas: Rp ";
                cin >> hargaInput;
                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    throw invalid_argument("❌ Input harga tidak valid!");
                }
                if (hargaInput <= 0)
                    throw invalid_argument("❌ Harga harus lebih dari 0!");
                validHarga = true;
            }
            catch (const exception &e)
            {
                cout << endl
                     << e.what() << " Silakan coba lagi.\n";
            }
        }

        int kapasitasInput = inputInteger("👥 Kapasitas Peserta: ");
        if (kapasitasInput <= 0)
            throw invalid_argument("❌ Kapasitas harus lebih dari 0!");

        int newID = 1;
        for (int i = 0; i < jumlahJadwal; i++)
            if (dataJadwal[i].jadwalID >= newID)
                newID = dataJadwal[i].jadwalID + 1;

        dataJadwal[jumlahJadwal].jadwalID = newID;
        dataJadwal[jumlahJadwal].hari = hariInput;
        dataJadwal[jumlahJadwal].jam = jamInput;
        dataJadwal[jumlahJadwal].jenisKelas = jenisInput;
        dataJadwal[jumlahJadwal].kategori = kategoriInput;
        dataJadwal[jumlahJadwal].instruktur = instrukturInput;
        dataJadwal[jumlahJadwal].harga = hargaInput;
        dataJadwal[jumlahJadwal].kapasitas = kapasitasInput;
        dataJadwal[jumlahJadwal].terisi = 0;
        jumlahJadwal++;

        simpanJadwal(dataJadwal, jumlahJadwal);

        loadingAnimation();
        cout << "✅ Jadwal berhasil ditambahkan!\n";
        cout << "🆔 ID Jadwal: " << newID << "\n\n";
    }
    catch (const exception &e)
    {
        cout << endl
             << e.what() << "\n\n";
    }
}

void lihatJadwal(JadwalKelas *dataJadwal, int jumlahJadwal)
{
    system("cls");
    tampilkanLogoKecil();
    cout << "====================================================\n";
    cout << "||            📋 LIHAT JADWAL KELAS 📋            ||\n";
    cout << "====================================================\n";

    JadwalKelas temp[30];
    for (int i = 0; i < jumlahJadwal; i++)
        temp[i] = dataJadwal[i];

    for (int i = 0; i < jumlahJadwal - 1; i++)
    {
        int minIndex = i;
        for (int j = i + 1; j < jumlahJadwal; j++)
            if (temp[j].kategori < temp[minIndex].kategori)
                minIndex = j;

        if (minIndex != i)
            swap(temp[i], temp[minIndex]);
    }

    cout << "==========================================================================================================\n";
    cout << "||                                    📅 DAFTAR JADWAL KELAS 📅                                         ||\n";
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
        cout << "❌ Belum ada data jadwal!\n";
    else
        for (int i = 0; i < jumlahJadwal; i++)
        {
            int sisa = temp[i].kapasitas - temp[i].terisi;
            cout << left << setw(5) << temp[i].jadwalID;
            cout << setw(10) << temp[i].hari;
            cout << setw(15) << temp[i].jam;
            cout << setw(18) << temp[i].jenisKelas;
            cout << setw(15) << temp[i].kategori;
            cout << setw(15) << temp[i].instruktur;
            cout << setw(12) << formatRupiah(temp[i].harga);
            cout << temp[i].terisi << "/" << temp[i].kapasitas
                 << " (sisa " << sisa << ")" << endl;
        }

    cout << "==========================================================================================================\n\n";

    cout << "🔍 Ingin mencari jadwal berdasarkan ID?\n";
    cout << "   1. ✅ Ya, cari jadwal\n";
    cout << "   0. ⬅️ Kembali\n";
    cout << "----------------------------------------------------\n";

    try
    {
        int pilihan = inputInteger(" 🎯 Pilihan (1/0): ");

        if (pilihan == 1)
        {
            system("cls");
            tampilkanLogoKecil();
            cout << "====================================================\n";
            cout << "||        🔎 CARI JADWAL BERDASARKAN ID 🔎        ||\n";
            cout << "====================================================\n";

            tampilkanDaftarJadwal(dataJadwal, jumlahJadwal);

            int targetID;
            while (true)
            {
                try
                {
                    targetID = inputInteger("\n🆔 Masukkan ID Jadwal yang dicari: ");
                    validasiID(targetID);
                    break;
                }
                catch (const exception &e)
                {
                    cout << endl
                         << e.what() << " Silakan coba lagi.\n";
                }
            }

            cout << "\n🎯 Target ID: " << targetID << endl;
            cout << "---------------------------------------\n";

            int hasil = -1, jumlahCek = 0;
            for (int i = 0; i < jumlahJadwal && hasil == -1; i++)
            {
                jumlahCek++;
                cout << "🔍 Cek jadwal ke-" << jumlahCek << ": ID " << dataJadwal[i].jadwalID;

                if (dataJadwal[i].jadwalID == targetID)
                {
                    cout << " >>> ✅ COCOK!\n";
                    hasil = i;
                }
                else
                    cout << " (❌ tidak cocok)\n";
            }
            cout << "---------------------------------------\n";

            if (hasil != -1)
            {
                cout << "🎉 Ditemukan setelah " << jumlahCek << " pengecekan!\n\n";
                cout << "===============================================\n";
                cout << "||          ✅ JADWAL DITEMUKAN! ✅          ||\n";
                cout << "===============================================\n";
                cout << "🆔 ID         : " << dataJadwal[hasil].jadwalID << endl;
                cout << "📅 Hari       : " << dataJadwal[hasil].hari << endl;
                cout << "🕐 Jam        : " << dataJadwal[hasil].jam << endl;
                cout << "🧘 Jenis      : " << dataJadwal[hasil].jenisKelas << endl;
                cout << "📌 Kategori   : " << dataJadwal[hasil].kategori << endl;
                cout << "👨‍🏫 Instruktur : " << dataJadwal[hasil].instruktur << endl;
                cout << "💰 Harga      : " << formatRupiah(dataJadwal[hasil].harga) << endl;
                cout << "👥 Kapasitas  : " << dataJadwal[hasil].terisi << "/" << dataJadwal[hasil].kapasitas << endl;
                cout << "===============================================\n";
            }
            else
                cout << "❌ Jadwal dengan ID " << targetID << " tidak ditemukan!\n";

            cout << "\n";
        }
        else if (pilihan == 0)
        {
            return;
        }
        else
        {
            cout << "\n❌ Pilihan tidak valid!\n";
        }
    }
    catch (const exception &e)
    {
        cout << endl
             << e.what() << "\n\n";
    }
}

void updateJadwal(JadwalKelas *dataJadwal, int jumlahJadwal)
{
    system("cls");
    tampilkanLogoKecil();
    cout << "====================================================\n";
    cout << "||             ✏️ UPDATE JADWAL KELAS ✏️          ||\n";
    cout << "====================================================\n";

    if (jumlahJadwal == 0)
    {
        cout << "❌ Data jadwal masih kosong!\n\n";
        return;
    }

    tampilkanDaftarJadwal(dataJadwal, jumlahJadwal);
    cout << "\n";

    int idCari = inputInteger("🆔 Masukkan ID Jadwal yang ingin diubah: ");
    bool ditemukan = false;

    for (int i = 0; i < jumlahJadwal; i++)
    {
        if (dataJadwal[i].jadwalID == idCari)
        {
            ditemukan = true;
            cout << "===============================================\n";
            cout << "||          📝 MASUKKAN DATA BARU 📝         ||\n";
            cout << "===============================================\n";
            cin.ignore(1000, '\n');
            string inputBaru;

            cout << "📅 Hari (sekarang: " << dataJadwal[i].hari << "): ";
            getline(cin, inputBaru);
            if (!inputBaru.empty())
            {
                validasiHari(inputBaru);
                dataJadwal[i].hari = inputBaru;
            }

            cout << "🕐 Jam (sekarang: " << dataJadwal[i].jam << "): ";
            getline(cin, inputBaru);
            if (!inputBaru.empty())
            {
                validasiJam(inputBaru);
                dataJadwal[i].jam = inputBaru;
            }

            cout << "🧘 Jenis Kelas (sekarang: " << dataJadwal[i].jenisKelas << "): ";
            getline(cin, inputBaru);
            if (!inputBaru.empty())
            {
                validasiHurufSpasi(inputBaru, "Jenis kelas");
                dataJadwal[i].jenisKelas = inputBaru;
            }

            cout << "📌 Kategori (sekarang: " << dataJadwal[i].kategori << "): ";
            getline(cin, inputBaru);
            if (!inputBaru.empty())
            {
                validasiHurufSpasi(inputBaru, "Kategori");
                dataJadwal[i].kategori = inputBaru;
            }

            cout << "👩‍🏫 Instruktur (sekarang: " << dataJadwal[i].instruktur << "): ";
            getline(cin, inputBaru);
            if (!inputBaru.empty())
            {
                validasiHurufSpasi(inputBaru, "Instruktur");
                dataJadwal[i].instruktur = inputBaru;
            }

            cout << "💰 Harga (sekarang: " << formatRupiah(dataJadwal[i].harga) << "): Rp ";
            string hargaStr;
            getline(cin, hargaStr);
            if (!hargaStr.empty())
            {
                int hargaBaru = stoi(hargaStr);
                if (hargaBaru > 0)
                    dataJadwal[i].harga = hargaBaru;
            }

            cout << "👥 Kapasitas (sekarang: " << dataJadwal[i].kapasitas << "): ";
            string kapasitasStr;
            getline(cin, kapasitasStr);
            if (!kapasitasStr.empty())
            {
                int kapasitasBaru = stoi(kapasitasStr);
                if (kapasitasBaru > 0)
                    dataJadwal[i].kapasitas = kapasitasBaru;
            }

            simpanJadwal(dataJadwal, jumlahJadwal);

            loadingAnimation();
            cout << "✅ Data Jadwal Berhasil Diperbarui!\n\n";
            break;
        }
    }

    if (!ditemukan)
    {
        cout << "\n❌ ID Jadwal tidak ditemukan.\n\n";
    }
}

void hapusJadwal(JadwalKelas *dataJadwal, int &jumlahJadwal)
{
    system("cls");
    tampilkanLogoKecil();
    cout << "====================================================\n";
    cout << "||            🗑️ HAPUS JADWAL KELAS 🗑️            ||\n";
    cout << "====================================================\n";

    if (jumlahJadwal == 0)
    {
        cout << "❌ Data jadwal masih kosong!\n\n";
        return;
    }

    tampilkanDaftarJadwal(dataJadwal, jumlahJadwal);
    cout << "\n";

    int idCari = inputInteger("🆔 Masukkan ID Jadwal yang ingin dihapus: ");
    int indexKetemu = -1;

    for (int i = 0; i < jumlahJadwal; i++)
    {
        if (dataJadwal[i].jadwalID == idCari)
        {
            indexKetemu = i;
            break;
        }
    }

    if (indexKetemu != -1)
    {
        cout << "\n🗑️ Menghapus jadwal: " << dataJadwal[indexKetemu].jenisKelas
             << " (" << dataJadwal[indexKetemu].kategori << ")"
             << " - " << dataJadwal[indexKetemu].hari
             << " " << dataJadwal[indexKetemu].jam << "\n";

        for (int i = indexKetemu; i < jumlahJadwal - 1; i++)
            dataJadwal[i] = dataJadwal[i + 1];
        jumlahJadwal--;

        simpanJadwal(dataJadwal, jumlahJadwal);

        loadingAnimation();
        cout << "✅ Jadwal Berhasil Dihapus!\n\n";
    }
    else
    {
        cout << "\n❌ ID tidak ditemukan.\n\n";
    }
}

void approvalBooking(Booking *dataBooking, int jumlahBooking, Akun *dataAkun, int jumlahAkun)
{
    system("cls");
    tampilkanLogoKecil();
    cout << "====================================================\n";
    cout << "||             ✅ APPROVAL BOOKING ✅             ||\n";
    cout << "====================================================\n";

    if (jumlahBooking == 0)
    {
        cout << "❌ Belum ada data booking.\n\n";
        return;
    }

    cout << "\n";
    cout << "=====================================================================================\n";
    cout << left << setw(10) << "BookingID"
         << setw(18) << "Nama Member"
         << setw(10) << "MemberID"
         << setw(12) << "Kelas"
         << setw(18) << "Harga"
         << "Status" << endl;
    cout << "-------------------------------------------------------------------------------------\n";

    bool adaPending = false;
    for (int i = 0; i < jumlahBooking; i++)
    {
        if (dataBooking[i].status == "pending")
        {
            adaPending = true;
            cout << "    " << left << setw(10) << dataBooking[i].bookingID
                 << setw(18) << dataBooking[i].namaMember
                 << setw(10) << dataBooking[i].memberID
                 << setw(12) << dataBooking[i].jenisKelas
                 << setw(18) << "💰 " + formatRupiah(dataBooking[i].harga)
                 << "⏳ " << dataBooking[i].status << "\n";
        }
    }

    if (!adaPending)
    {
        cout << "✅ Tidak ada booking yang menunggu approval\n";
        cout << "=====================================================================================\n";
        return;
    }
    cout << "=====================================================================================\n";

    try
    {
        int bookingID = inputInteger("\n🆔 Masukkan Booking ID yang ingin diproses: ");

        int index = -1;
        for (int i = 0; i < jumlahBooking; i++)
        {
            if (dataBooking[i].bookingID == bookingID && dataBooking[i].status == "pending")
            {
                index = i;
                break;
            }
        }

        if (index == -1)
            throw runtime_error("❌ Booking ID tidak ditemukan atau sudah diproses!");

        cout << "\n========================================\n";
        cout << "||         📋 DETAIL BOOKING 📋       ||\n";
        cout << "========================================\n";
        cout << left << setw(15) << "🆔 Booking ID" << ": " << dataBooking[index].bookingID << "\n";
        cout << left << setw(15) << "👤 Nama Member" << ": " << dataBooking[index].namaMember << "\n";
        cout << left << setw(15) << "🧘 Kelas" << ": " << dataBooking[index].jenisKelas << "\n";
        cout << left << setw(15) << "💰 Harga" << ": " << formatRupiah(dataBooking[index].harga) << "\n";
        cout << "----------------------------------------\n";
        cout << "1. ✅ Approve\n";
        cout << "2. ❌ Reject\n";

        int pilihan = inputInteger("\n🎯 Pilihan (1/2): ");

        if (pilihan == 1)
        {
            dataBooking[index].status = "approved";
            loadingAnimation();
            cout << "✅ Booking berhasil di-approve!\n\n";
        }
        else if (pilihan == 2)
        {
            dataBooking[index].status = "rejected";

            int indexMember = cariusername(dataAkun, jumlahAkun, dataBooking[index].namaMember);
            if (indexMember != -1)
            {
                dataAkun[indexMember].saldo += dataBooking[index].harga;
            }
            loadingAnimation();
            cout << "❌ Booking di-reject! 💰 Saldo member dikembalikan.\n\n";
        }
        else
            throw out_of_range("❌ Pilihan tidak valid!");
    }
    catch (const exception &e)
    {
        cout << endl
             << e.what() << "\n\n";
    }
}

#endif