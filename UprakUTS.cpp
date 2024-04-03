#include <iostream>
#include <string>
#include <cstring>
#include <iomanip>

using namespace std;

// Struktur data untuk menyimpan informasi pemesanan kursi
struct booking {
    int nokursi;            // Nomor kursi
    char nama[50], tujuan[50], nik[50];    // Informasi penumpang (nama, tujuan, NIK)
    bool tersedia;          // Status ketersediaan kursi
    booking *next, *prev;   // Pointer untuk linked list
};

booking *awal = NULL, *akhir = NULL;    // Pointer awal dan akhir dari linked list

// Fungsi untuk menambahkan pemesanan kursi baru
void tambahBooking(int nokursi, char nama[50], char tujuan[50], char nik[50]) {
    booking *baru = new booking;    // Membuat node baru untuk pemesanan kursi
    baru->nokursi = nokursi;
    strcpy(baru->nama, nama);       //strcpy untuk menyalin isi dari satu char ke string lainnya
    strcpy(baru->tujuan, tujuan);   //atau dari string ke string lainnya
    strcpy(baru->nik, nik);
    baru->tersedia = false;         // Awalnya dianggap tidak tersedia
    baru->next = NULL;              // Pointer next awalnya menunjuk ke NULL
    baru->prev = akhir;             // Pointer prev menunjuk ke node sebelumnya (akhir)

    // Memperbarui pointer awal dan akhir jika linked list masih kosong
    if (awal == NULL) {
        awal = baru;
    } else {
        akhir->next = baru;         // Menambahkan node baru setelah node terakhir
    }
    akhir = baru;                  // Memperbarui pointer akhir ke node baru
}

// Fungsi untuk menampilkan daftar kursi beserta statusnya
void tampilkanKursi() {
    booking *bantu = awal;         // Pointer bantu untuk traversal linked list
    if (awal == NULL) {
        // Jika linked list kosong, tampilkan pesan
        cout << "-----------------------" << endl;
        cout << "| Semua kursi kosong! |" << endl;
        cout << "-----------------------" << endl;
    } else {
        // Jika linked list tidak kosong, tampilkan daftar kursi
        cout << setfill('-') << setw(60) << "-" << setfill(' ') << "\n";
        cout << "Daftar Kursi:\n";
        cout << "Ket : P    = terisi \n      1-20 = belum terisi \n";
        cout << setfill('-') << setw(60) << "-" << setfill(' ') << "\n";
        for (int i = 0; i < 20; i++) {
            bool ditemukan = false;
            while (bantu != NULL) {
                if (bantu->nokursi == i + 1) {
                    // Jika kursi terisi, tampilkan "P"
                    cout << setw(2) << "|" << setw(2) << "P" << setw(2) << "|" << setw(2);
                    ditemukan = true;
                    bantu = bantu->next;
                    break;
                }
                bantu = bantu->next;
            }
            if (i == 10) {
                // Tambahkan garis pemisah setelah baris ke-10
                cout << "\n" << setfill('-') << setw(60) << "-" << setfill(' ') << "\n";
                cout << setfill('-') << setw(60) << "-" << setfill(' ') << "\n";
            }
            if (!ditemukan) {
                // Jika kursi kosong, tampilkan nomor kursi
                cout << setw(2) << "|" << setw(2) << i + 1 << setw(2) << "|" << setw(2);
            }
            bantu = awal;
        }
        cout << "\n" << setfill('-') << setw(60) << "-" << setfill(' ') << "\n";
        // Menampilkan data lengkap pemesanan
        cout << setfill('-') << setw(42) << "-" << setfill(' ') << "\n";
        cout << "| Kursi | NIK      | Nama     | Tujuan   |\n";
        cout << setfill('-') << setw(42) << "-" << setfill(' ') << "\n";
        for (int i = 0; i < 20; i++) {
            bool ditemukan = false;
            while (bantu != NULL) {
                if (bantu->nokursi == i+1) {
                    cout << "| " << setw(5) << bantu->nokursi
                        << " | " << setw(8) << bantu->nik
                        << " | " << setw(8) << bantu->nama
                        << " | " << setw(8) << bantu->tujuan
                        << " |\n";
                    ditemukan = true;
                    bantu = bantu->next;
                    break;
                }
                bantu = bantu->next;
            }
            if (!ditemukan) {
                cout << "| " << setw(5) << i+1
                    << " | " << setw(8) << "..."
                    << " | " << setw(8) << "..."
                    << " | " << setw(8) << "..."
                    << " |\n";
            }
            bantu = awal;
        }
        cout << setfill('-') << setw(42) << "-" << setfill(' ') << "\n";
    }
}

// Fungsi untuk melakukan pemesanan kursi
void bookingkursi() {
    int tambahan;
    int nomor;

    cout << "Masukan jumlah kursi yang ingin anda pesan : ";
    cin >> tambahan;

    for (int i = 0; i < tambahan; i++) {
        int nomor;
        do {
            cout << "Masukan nomor kursi    : ";
            cin >> nomor;
            if (nomor >= 0 && nomor < 20) {
                booking *bantu = awal;
                bool tersedia = true;
                while (bantu != NULL) {
                    if (bantu->nokursi == nomor) {
                        tersedia = false;
                        break;
                    }
                    bantu = bantu->next;
                }
                if (tersedia) {
                    char nama[50], tujuan[50], nik[50];
                    cout << "Masukan NIK            : ";
                    cin >> nik;
                    cout << "Masukan Nama           : ";
                    cin >> nama;
                    cout << "Masukan tujuan         : ";
                    cin >> tujuan;
                    tambahBooking(nomor, nama, tujuan, nik);
                    break;
                } else {
                    cout << "---------------------------------------------------" << endl;
                    cout << "| Kursi sudah tidak tersedia, silahkan pesan ulang!|" << endl;
                    cout << "---------------------------------------------------" << endl;
                }
            } else {
                cout << "--------------------------------------------------------" << endl;
                cout << "| Nomor kursi tidak ada di kereta, silahkan pesan ulang!|" << endl;
                cout << "--------------------------------------------------------" << endl;
            }
        } while (true);
    }
}

// Fungsi untuk menukar posisi kursi
void tukarKursi() {
    int kursi1, kursi2;
    cout << "Masukkan nomor kursi yang ingin ditukar : ";
    cin >> kursi1;
    cout << "Masukan nomor kursi penggantinya : ";
    cin >> kursi2;

    // Cari booking untuk kedua kursi
    booking *booking1 = NULL, *booking2 = NULL;
    for (booking *bantu = awal; bantu != NULL; bantu = bantu->next) {
        if (bantu->nokursi == kursi1) {
            booking1 = bantu;
        } else if (bantu->nokursi == kursi2) {
            booking2 = bantu;
        }
    }

    // Jika kedua booking ditemukan, tukar informasi pemesan di antara mereka
    if (booking1 != NULL && booking2 != NULL) {
        char tempNama[50], tempTujuan[50], tempNik[50];
        strcpy(tempNama, booking1->nama);
        strcpy(tempTujuan, booking1->tujuan);
        strcpy(tempNik, booking1->nik);

        strcpy(booking1->nama, booking2->nama);
        strcpy(booking1->tujuan, booking2->tujuan);
        strcpy(booking1->nik, booking2->nik);

        strcpy(booking2->nama, tempNama);
        strcpy(booking2->tujuan, tempTujuan);
        strcpy(booking2->nik, tempNik);

        cout << "---------------------------------------\n";
        cout << "| Penukaran kursi berhasil dilakukan! |\n";
        cout << "---------------------------------------\n";
    } else {
        cout << "------------------------------------------------\n";
        cout << "| Salah satu atau kedua kursi tidak ditemukan! |\n";
        cout << "------------------------------------------------\n";
    }
}

// Fungsi untuk membatalkan pesanan kursi
void batalPesanan() {
    if (awal == NULL) {
        // Jika linked list kosong, tampilkan pesan
        cout << "-----------------------" << endl;
        cout << "| Semua kursi kosong! |" << endl;
        cout << "-----------------------" << endl;
    } else {
        int kursi;
        booking *bantu = awal, *prev = NULL;

        cout << "Masukkan nomor kursi yang ingin dibatalkan: ";
        cin >> kursi;

        // Cari node kursi yang ingin dibatalkan
        while (bantu != NULL) {
            if (bantu->nokursi == kursi) {
                break;
            }
            prev = bantu;
            bantu = bantu->next;
        }

        // Jika node tidak ditemukan
        if (bantu == NULL) {
            cout << "----------------------------" << endl;
            cout << "Kursi " << kursi << " tidak ditemukan." << endl;
            cout << "----------------------------" << endl;
            return;
        }
        // Memastikan apakah pengguna ingin membatalkan pemesanan
        int pilih;
        cout << "NIK    : " << bantu->nik << endl;
        cout << "Nama   : " << bantu->nama << endl;
        cout << "tujuan : " << bantu->tujuan << endl;
        cout << "Apakah yakin untuk membatalkan pesanan? (1=ya/2=tidak) :";
        cin >> pilih;

        if (pilih == 1){
            // Jika node adalah node awal
            if (prev == NULL) {
                awal = bantu->next;
            } else {
                prev->next = bantu->next;
            }
            // Jika node adalah node akhir
            if (bantu == akhir) {
                akhir = prev;
            }
            // Hapus node
            delete bantu;
            cout << "------------------------------------------" << endl;
            cout << "| Pemesanan kursi " << kursi << " berhasil dibatalkan! |" << endl;
            cout << "------------------------------------------" << endl;
            return;
        }else if (pilih == 2){
            cout << "-------------------------------------" << endl;
            cout << "| Baik, terima kasih telah memesan! |" << endl;
            cout << "-------------------------------------" << endl;
            return;
        }else{
            cout << "-------------------------------------------------------" << endl;
            cout << "| Kode tidak valid, kamu akan kembali pada menu awal! |" << endl;
            cout << "-------------------------------------------------------" << endl;
            return;
        }
    }
}

int main() {
    int pilihan;
    do {
        cout << "Silahkan memilih menu yang ada!" << endl;
        cout << "1. Menampilkan kursi kereta" << endl;
        cout << "2. Pemesanan kursi kereta" << endl;
        cout << "3. Menukar posisi kursi kereta" << endl;
        cout << "4. Membatalkan Pemesanan Kursi" << endl;
        cout << "5. Keluar Program!" << endl;
        cout << "Masukan Pilihan : ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                tampilkanKursi();
                break;
            case 2:
                bookingkursi();
                break;
            case 3:
                tukarKursi();
                break;
            case 4:
                batalPesanan();
                break;
            case 5:
                cout << "-----------------" << endl;
                cout << "| Terima kasih! |" << endl;
                cout << "-----------------" << endl;
                break;
            default:
                cout << "------------------------" << endl;
                cout << "| Pilihan tidak valid! |" << endl;
                cout << "------------------------" << endl;
        }
    } while (pilihan != 5);

    return 0;
}
