// Raymond Thymotimannuel
// 2309106067
// Informatika B1'23
// Praktikum APL Post Test 3

#include <iostream>
#include <string>
#include <cstring>

using namespace std;

const int MAX_TEMPAT = 10;

// Deklarasi struct TempatMakan
struct TempatMakan {
    string nama;
};

// Deklarasi struct Pengguna
struct Pengguna {
    string nama;
    string kataSandi;
};

// Deklarasi struct DaftarTempatMakan
struct DaftarTempatMakan {
    TempatMakan tempatMakan[MAX_TEMPAT];
    int jumlahTempat;
};

// Fungsi untuk melakukan login
bool lakukanLogin(Pengguna pengguna) {
    string inputNamaPengguna, inputKataSandi;
    int kesempatan = 0;
    while (kesempatan < 3) {
        cout << "Masukkan username: ";
        getline(cin, inputNamaPengguna);
        cout << "Masukkan password: ";
        getline(cin, inputKataSandi);
        if (inputNamaPengguna == pengguna.nama && inputKataSandi == pengguna.kataSandi) {
            return true;
        } else {
            kesempatan++;
            cout << "Username atau password Anda salah. Kesempatan login tersisa: " << 3 - kesempatan << endl;
        }
    }
    cout << "Percobaan terlalu banyak, silahkan coba lagi nanti!" << endl;
    return false;
}

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
void tampilkanTempatMakan(DaftarTempatMakan &daftar) {
    cout << "Daftar tempat makan favorit:\n";
    for (int i = 0; i < daftar.jumlahTempat; ++i) {
        cout << i + 1 << ") " << daftar.tempatMakan[i].nama << endl;
    }
    cout << "Tekan \"Enter\" untuk kembali\n";
    cin.ignore();
    cin.get();
}

// Prosedur menambahkan tempat makan ke dalam daftar
void tambahTempatMakan(DaftarTempatMakan &daftar) {
    if (daftar.jumlahTempat >= MAX_TEMPAT) {
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

    for (int i = 0; i < daftar.jumlahTempat; ++i) {
        if (namaBaru == daftar.tempatMakan[i].nama) {
            cout << "Nama tempat sudah terdaftar!\n";
            return;
        }
    }

    cout << "Tambahkan tempat makan ini ke dalam daftar? (y/n): ";
    char pilihan;
    cin >> pilihan;

    if (pilihan == 'y') {
        daftar.tempatMakan[daftar.jumlahTempat].nama = namaBaru;
        ++daftar.jumlahTempat;
        cout << "Tempat berhasil ditambahkan!\n";
    } else if (pilihan == 'n') {
        cout << "Input dibatalkan\n";
    } else {
        cout << "Input tidak valid!\n";
    }
}

// Prosedur memperbarui nama tempat makan dalam daftar
void perbaruiTempatMakan(DaftarTempatMakan &daftar) {
    tampilkanTempatMakan(daftar);
    cout << "Pilih daftar tempat makan yang ingin diperbarui (0 untuk kembali): ";
    int pilihan;
    cin >> pilihan;

    if (pilihan == 0) {
        return;
    }

    if (pilihan > 0 && pilihan <= daftar.jumlahTempat) {
        cout << "Silahkan masukkan perbaruan pada tempat ini: ";
        cin.ignore();
        getline(cin, daftar.tempatMakan[pilihan - 1].nama);
        cout << "Tempat telah diperbarui!\n";
    } else {
        cout << "Opsi yang Anda pilih tidak terdaftar, silahkan coba lagi!\n";
        perbaruiTempatMakan(daftar);
    }
}

// Prosedur menghapus tempat makan dari daftar
void hapusTempatMakan(DaftarTempatMakan &daftar) {
    tampilkanTempatMakan(daftar);
    cout << "Pilih daftar tempat makan yang ingin dihapus (0 untuk kembali): ";
    int pilihan;
    cin >> pilihan;

    if (pilihan == 0) {
        return;
    }

    if (pilihan > 0 && pilihan <= daftar.jumlahTempat) {
        cout << "Hapus daftar ini dari list? (y/n): ";
        char konfirmasi;
        cin >> konfirmasi;

        if (konfirmasi == 'y') {
            for (int i = pilihan - 1; i < daftar.jumlahTempat - 1; ++i) {
                daftar.tempatMakan[i] = daftar.tempatMakan[i + 1];
            }
            --daftar.jumlahTempat;
            cout << "Tempat telah dihapus!\n";
        } else if (konfirmasi == 'n') {
            cout << "Opsi dibatalkan!\n";
        } else {
            cout << "Input tidak valid, silahkan coba lagi!\n";
            hapusTempatMakan(daftar);
        }
    } else {
        cout << "Opsi yang Anda pilih tidak terdaftar, silahkan coba lagi!\n";
        hapusTempatMakan(daftar);
    }
}

// Prosedur yang mengintegrasikan login dan CRUD
void jalankanProgram(Pengguna &pengguna, DaftarTempatMakan &daftar) {
    bool sudahLogin = lakukanLogin(pengguna);

    if (sudahLogin) {
        int pilihan;
        do {
            tampilkanMenuUtama();
           
            cin >> pilihan;

            switch (pilihan) {
                case 1:
                    tampilkanTempatMakan(daftar);
                    break;
                case 2:
                    tambahTempatMakan(daftar);
                    break;
                case 3:
                    perbaruiTempatMakan(daftar);
                    break;
                case 4:
                    hapusTempatMakan(daftar);
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

int main() {
    Pengguna pengguna = {"Raymond Thymotimannuel", "2309106067"};
    DaftarTempatMakan daftar;
    daftar.jumlahTempat = 3;
    daftar.tempatMakan[0].nama = "Restoran Kampung Lauk";
    daftar.tempatMakan[1].nama = "Bistro Jawara";
    daftar.tempatMakan[2].nama = "Warung Makan Ayam Jontor";

    jalankanProgram(pengguna, daftar);

    return 0;
}
