// Raymond Thymotimannuel
// 2309106067
// Informatika B1'23
// Praktikum APL Post Test 3

#include <iostream>
#include <string>
#include <cstring>

using namespace std;

string namaPengguna = "Raymond Thymotimannuel";
string kataSandi = "2309106067";
bool sudahLogin = false; // fungsi dari login

const int MAKS_TEMPAT = 10; // Jumlah maksimal item yang bisa ditampung daftar
char tempatMakan[MAKS_TEMPAT][50] = {
    "Restoran Kampung Lauk",
    "Bistro Jawara",
    "Warung Makan Ayam Jontor"
}; // Daftar tempat makan bawaan, array maksimal 50 karakter yang bisa digunakan ketika input nama tempat makan
int jumlahTempat = 3;

// Prosedur menampilkan menu utama
void tampilkanMenuUtama() {
    cout << "Selamat datang di program Daftar Tempat Makan Favorit!\n";
    cout << "Silahkan pilih menu\n";
    cout << "1) Lihat daftar tempat makan\n";
    cout << "2) Tambah tempat makan\n";
    cout << "3) Perbarui tempat makan\n";
    cout << "4) Hapus tempat makan\n";
    cout << "0) Keluar\n";
    cout << "Masukkan pilihan (1/2/3/4/0): ";
}

// Prosedur menampilkan daftar tempat makan
void tampilkanTempatMakan() {
    cout << "Daftar tempat makan favorit:\n";
    for (int i = 0; i < jumlahTempat; ++i) {
        cout << i + 1 << ") " << tempatMakan[i] << endl;
    }
    cout << "Tekan \"Enter\" untuk kembali\n";
    cin.ignore();
    cin.get();
}

// Prosedur menambahkan tempat makan ke dalam daftar
void tambahTempatMakan() {
    if (jumlahTempat >= MAKS_TEMPAT) {
        cout << "Maaf, daftar tempat makan sudah penuh. Tidak dapat menambahkan lagi.\n";
        return;
    }

    string namaBaru;
    cout << "Masukkan nama tempat makan (maksimal 49 karakter): ";
    cin.ignore();
    getline(cin, namaBaru);

    if (namaBaru.length() >= 50) {
        cout << "Nama tempat makan terlalu panjang!\n";
        return;
    }

    for (int i = 0; i < jumlahTempat; ++i) {
        if (namaBaru == tempatMakan[i]) {
            cout << "Nama tempat sudah terdaftar!\n";
            return;
        }
    }

    cout << "Tambahkan tempat makan ini ke dalam daftar? (y/n): ";
    char pilihan;
    cin >> pilihan;

    if (pilihan == 'y') {
        strcpy(tempatMakan[jumlahTempat], namaBaru.c_str());
        ++jumlahTempat;
        cout << "Tempat berhasil ditambahkan!\n";
    } else if (pilihan == 'n') {
        cout << "Input dibatalkan\n";
    } else {
        cout << "Input tidak valid!\n";
    }
}

// Prosedur memperbarui nama tempat makan dalam daftar
void perbaruiTempatMakan() {
    tampilkanTempatMakan();
    cout << "Pilih daftar tempat makan yang ingin diperbarui (0 untuk kembali): ";
    int pilihan;
    cin >> pilihan;

    if (pilihan == 0) {
        return;
    }

    if (pilihan > 0 && pilihan <= jumlahTempat) {
        cout << "Silahkan masukkan perbaruan pada tempat ini: ";
        cin.ignore();
        cin.getline(tempatMakan[pilihan - 1], sizeof(tempatMakan[pilihan - 1]));
        cout << "Tempat telah diperbarui!\n";
    } else {
        cout << "Opsi yang Anda pilih tidak terdaftar, silahkan coba lagi!\n";
        perbaruiTempatMakan(); // Rekursif dari perbaruiTempatMakan terjadi ketika inputan dari pilihan tidak memenuhi syarat (y/n)
    }
}

// Proseduur menghapus tempat makan dari daftar
void hapusTempatMakan() {
    tampilkanTempatMakan();
    cout << "Pilih daftar tempat makan yang ingin dihapus (0 untuk kembali): ";
    int pilihan;
    cin >> pilihan;

    if (pilihan == 0) {
        return;
    }

    if (pilihan > 0 && pilihan <= jumlahTempat) {
        cout << "Hapus daftar ini dari list? (y/n): ";
        char konfirmasi;
        cin >> konfirmasi;

        if (konfirmasi == 'y') {
            for (int i = pilihan - 1; i < jumlahTempat - 1; ++i) {
                strcpy(tempatMakan[i], tempatMakan[i + 1]);
            }
            --jumlahTempat;
            cout << "Tempat telah dihapus!\n";
        } else if (konfirmasi == 'n') {
            cout << "Opsi dibatalkan!\n";
        } else {
            cout << "Input tidak valid, silahkan coba lagi!\n";
            hapusTempatMakan(); // Rekursif dari hapusTempatMakan terjadi ketika inputan dari konfirmasi tidak memenuhi syarat (y/n)
        }
    } else {
        cout << "Opsi yang Anda pilih tidak terdaftar, silahkan coba lagi!\n";
        hapusTempatMakan();
    }
}

// Fungsi untuk melakukan login
bool lakukanLogin() {
    string inputNamaPengguna, inputKataSandi;
    int kesempatan = 0;
    while (kesempatan < 3) {
        cout << "Masukkan username: ";
        getline(cin, inputNamaPengguna);
        cout << "Masukkan password: ";
        getline(cin, inputKataSandi);
        if (inputNamaPengguna == namaPengguna && inputKataSandi == kataSandi) {
            return true;
        } else {
            kesempatan++;
            cout << "Username atau password Anda salah. Kesempatan login tersisa: " << 3 - kesempatan << endl;
        }
    }
    cout << "Percobaan terlalu banyak, silahkan coba lagi nanti!" << endl;
    return false;
}

// Prosedur yang mengintegrasikan login dan CRUD
void jalankanProgram() {
    sudahLogin = lakukanLogin();

    if (sudahLogin) {
        int pilihan;
        do {
            tampilkanMenuUtama();
            cin >> pilihan;

            switch (pilihan) {
                case 1:
                    tampilkanTempatMakan();
                    break;
                case 2:
                    tambahTempatMakan();
                    break;
                case 3:
                    perbaruiTempatMakan();
                    break;
                case 4:
                    hapusTempatMakan();
                    break;
                case 0:
                    cout << "Terima kasih telah menggunakan program ini!\n";
                    sudahLogin = false;
                    break;
                default:
                    cout << "Opsi tidak tersedia, silahkan pilih lagi!\n";
                    break;
            }
        } while (pilihan != 0);
    }
}

int main() { // Fungsi untuk menjalankan program utama sebagai eksekusi awal
    jalankanProgram();

    return 0;
}
