#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

//struktur untuk menyimpan data pengguna
struct User {
    string username;
    string password;
};

//struktur untuk menyimpan data soal pilihan ganda
struct pilgan {
    string soal;
    string pilihan[4];
    string jawaban;
};

//struktur untuk menyimpan data skor pemain
struct Skor {
    string nama;
    string id;
    int nilai;
};

//variabel global
int jml_soal = 5;
int jml_buat;
int kesempatan = 3;
int nomor;
int idx;

//daftar soal pilihan ganda awal
vector<pilgan> pertanyaan = {
    {"Apa yang dimaksud dengan 'syntax error' dalam pemrograman?", {"Kesalahan dalam algoritma", "Kesalahan dalam logika program", "Kesalahan dalam penulisan kode program", "Kesalahan dalam pemrosesan input"}, "c"},
    {"Apa yang dilakukan oleh pernyataan 'break' dalam loop?", {"Mengakhiri loop dan melanjutkan eksekusi program berikutnya", "Melanjutkan loop ke iterasi berikutnya", "Mengakhiri program secara keseluruhan", "Menampilkan pesan kesalahan"}, "a"},
    {"Apa yang dimaksud dengan 'variable scope' dalam pemrograman?", {"Jarak antara dua titik dalam program", "Area di mana sebuah variabel dapat diakses", "Ukuran maksimum variabel yang dapat ditampung", "Jenis data yang dapat disimpan dalam variabel"}, "b"},
    {"Apa fungsi dari operator '==' dalam pemrograman?", {"Menetapkan nilai ke variabel", "Membandingkan dua nilai untuk kesamaan", "Menggabungkan dua nilai menjadi satu", "Memeriksa apakah nilai lebih besar dari yang lain"}, "b"},
    {"Apa perbedaan antara 'function' dan 'method' dalam pemrograman berorientasi objek?", {"Function tidak dapat digunakan di dalam class, sedangkan method dapat", "Function selalu mengembalikan nilai, sedangkan method tidak", "Function tidak memiliki parameter, sedangkan method memiliki", "Function berdiri sendiri, sedangkan method terkait dengan objek"}, "d"}
};

//daftar skor pemain
vector<Skor> papanSkor;

//deklarasi fungsi
void menu_utama();
void admin();
//void pemain();
void tentang();
void lanjut();
void permainan();
void menu_pemain();
void simpanSkorKeCSV(const Skor& pemainSkor);
string hasilkanIdUnik(const vector<string> &idTerpakai);
bool idUnik(const string &id, const vector<string> &idTerpakai);
void papan_skor();
void buat_kuis();
void lihat_kuis();
void perbarui_kuis();
void hapus_kuis();
void baca_tentang();
void muatSkorDariCSV();

//fungsi untuk login sebagai admin
bool login() {
    User akun_admin[3] = {
        {"Ray", "067"}, {"Bagus", "047"}, {"Daffatron", "063"}
    };
    string username, password;
    cout << "Masukkan username: ";
    cin >> username;
    cout << "Masukkan password: ";
    cin >> password;
    system("cls");

    for (int i = 0; i < 3; i++) {
        if (username == akun_admin[i].username && password == akun_admin[i].password) {
            cout << "Berhasil login" << endl;
            return true;
        }
    }
    if (kesempatan == 1) {
        cout << "Kesempatan telah habis\n"
             << "Segera mematikan program";
        exit(0);
    }
    kesempatan--;
    cout << "Username atau password salah\n";
    cout << "Sisa kesempatan: " << kesempatan << endl;
    lanjut();
    return false;
}

//fungsi untuk membuat soal kuis baru
void buat_kuis() {
    bool validInput = false;
    while (!validInput) {
    cout << "Silakan tentukan jumlah soal yang ingin dibuat: ";
    cin >> jml_buat;

    if (cin.fail() || jml_buat < 0) {
        cin.clear();
        cin.ignore();
        system("cls");
        cout << "Input tidak valid! Silakan masukkan pilihan yang benar.\n";
    } else {
        validInput = true;
    }
    }
    cout << "Tulis soal anda:\n";
    cin.ignore();
    for (int i = jml_soal; i < jml_soal + jml_buat; i++) {
        pilgan temp;
        cout << "Soal ke-" << i + 1 << endl;
        getline(cin, temp.soal);
        cout << "a. ";
        getline(cin, temp.pilihan[0]);
        cout << "b. ";
        getline(cin, temp.pilihan[1]);
        cout << "c. ";
        getline(cin, temp.pilihan[2]);
        cout << "d. ";
        getline(cin, temp.pilihan[3]);
        string jwb;
        while (true) {
            cout << "Jawaban (a/b/c/d): ";
            getline(cin, jwb);
            if (jwb.length() == 1&& (jwb == "a" || jwb == "b" || jwb == "c" || jwb == "d")){
                temp.jawaban = jwb;
                break;
            }else {
                cout << "Jawaban tidak valid. Silahkan masukkan jawaban berupa huruf a, b, c, atau d"<< endl;
            }
        };
        pertanyaan.push_back(temp);
    }
    jml_soal += jml_buat;
}

//fungsi untuk melihat semua soal kuis
void lihat_kuis() {
    for (int i = 0; i < jml_soal; i++) {
        cout << "Soal ke-" << i + 1 << endl;
        cout << pertanyaan[i].soal << endl;
        cout << "a. " << pertanyaan[i].pilihan[0] << endl;
        cout << "b. " << pertanyaan[i].pilihan[1] << endl;
        cout << "c. " << pertanyaan[i].pilihan[2] << endl;
        cout << "d. " << pertanyaan[i].pilihan[3] << endl;
        cout << "Jawaban: " << pertanyaan[i].jawaban << endl;
        cout << "\n";
    }
}

//fungsi untuk memperbarui soal kuis
void perbarui_kuis() {
    cout << "Masukkan nomor soal yang ingin diperbarui (1 - " << jml_soal << "): ";
    cin >> nomor;
    if (nomor < 1 || nomor > jml_soal) {
        cout << "Nomor soal tidak valid\n";
        return;
    }
    cin.ignore();
    idx = nomor - 1;
    cout << "Perbarui soal ke-" << nomor << endl;
    cout << "Soal baru: ";
    getline(cin, pertanyaan[idx].soal);
    cout << "a. ";
    getline(cin, pertanyaan[idx].pilihan[0]);
    cout << "b. ";
    getline(cin, pertanyaan[idx].pilihan[1]);
    cout << "c. ";
    getline(cin, pertanyaan[idx].pilihan[2]);
    cout << "d. ";
    getline(cin, pertanyaan[idx].pilihan[3]);
    string jwbb;
    while (true){
    cout << "Jawaban baru (a/b/c/d): ";
    getline(cin, jwbb);
    if (jwbb.length() == 1&& (jwbb == "a" || jwbb == "b" || jwbb == "c" || jwbb == "d")){
                pertanyaan[idx].jawaban = jwbb;
                break;
            }else {
                cout << "Jawaban tidak valid. Silahkan masukkan jawaban berupa huruf a, b, c, atau d"<< endl;
            }
    }
    
}

//fungsi untuk menghapus soal kuis
void hapus_kuis() {
    cout << "Masukkan nomor soal yang ingin dihapus (1 - " << jml_soal << "): ";
    cin >> idx;
    if (idx < 1 || idx > jml_soal) {
        system("cls");
        cout << "Nomor soal tidak valid\n";
        return;
    }
    else{
    pertanyaan.erase(pertanyaan.begin() + idx - 1);
    jml_soal--;
    system("cls");
    cout << "Soal telah dihapus\n";
    }
}

//fungsi untuk membaca informasi tentang aplikasi dari file CSV
void baca_tentang() {
    ifstream file("tentang.csv");
    string line;

    if (file.is_open()) {
        while (getline(file, line)) {
            cout << setw(80) << line << endl;
        }
        file.close();
    } else {
        cout << "Gagal membuka file tentang.csv\n";
    }
}

//menu utama untuk admin
void menu_admin() {
    system("cls");
    string pilihan;
    cout << "=== Selamat Datang, Min! ===\n"
         << "1) Buat kuis\n"
         << "2) Lihat kuis\n"
         << "3) Perbarui kuis\n"
         << "4) Hapus kuis\n"
         << "5) Kembali\n";
    cout << "Input: ";
    cin >> pilihan;
    system("cls");
    if (pilihan == "1") {
        buat_kuis();
        lanjut();
        menu_admin();
    } else if (pilihan == "2") {
        lihat_kuis();
        lanjut();
        menu_admin();
    } else if (pilihan == "3") {
        lihat_kuis();
        perbarui_kuis();
        lanjut();
        menu_admin();
    } else if (pilihan == "4") {
        lihat_kuis();
        hapus_kuis();
        lanjut();
        menu_admin();
    } else if (pilihan == "5") {
        lanjut();
        menu_utama();
    } else {
        cout << "Pilihan tidak ada\n";
        lanjut();
        menu_admin();
    }
}

//fungsi untuk login admin dan mengakses menu admin
void admin() {
    bool verifikasi = login();
    if (verifikasi) {
        menu_admin();
    } else {
        menu_utama();
    }
}

//menu utama untuk pemain
void menu_pemain() {
    system("cls");
    string pilihan;
    cout << "=== Selamat Datang Kuisisendiri! ===\n"
         << "1) Mulai Permainan\n"
         << "2) Lihat Skor\n"
         << "3) Kembali\n";
    cout << "Input: ";
    cin >> pilihan;
    system("cls");
    if (pilihan == "1") {
        permainan();
    } else if (pilihan == "2") {
        papan_skor();
    } else if (pilihan == "3") {
        menu_utama();
    } else {
        cout << "Pilihan tidak ada\n";
        lanjut();
        menu_pemain();
    }
}

//fungsi untuk memainkan kuis
void permainan() {
    int score = 0;
    string answer;
    for (int i = 0; i < jml_soal; i++) {
        cout << "Soal nomor " << i + 1 << ":\n"
             << pertanyaan[i].soal << endl;
        cout << "a. " << pertanyaan[i].pilihan[0] << endl;
        cout << "b. " << pertanyaan[i].pilihan[1] << endl;
        cout << "c. " << pertanyaan[i].pilihan[2] << endl;
        cout << "d. " << pertanyaan[i].pilihan[3] << endl;
        while (true){
            cout << "Jawaban: ";
            cin >> answer;
            if (answer.length() == 1&& (answer == "a" || answer == "b" || answer == "c" || answer == "d")){
                    break;
            }else {
                cout << "Jawaban tidak valid. Silahkan masukkan jawaban berupa huruf a, b, c, atau d"<<endl;
            }
        }
        transform(answer.begin(), answer.end(), answer.begin(), ::tolower);
        if (answer == pertanyaan[i].jawaban) {
            score += 20;
            cout << "Benar!\n";
        } else {
            cout << "Salah. Jawaban yang benar adalah " << pertanyaan[i].jawaban << ".\n";
        }
        cout << "\n";
    }
    cout << "Skor akhir: " << score << endl;
    Skor pemainSkor;
    cout << "Masukkan nama Anda: ";
    cin >> pemainSkor.nama;
    pemainSkor.nilai = score;
    vector<string> idTerpakai;
    for (const Skor &skor : papanSkor) {
        idTerpakai.push_back(skor.id);
    }
    pemainSkor.id = hasilkanIdUnik(idTerpakai);
    papanSkor.push_back(pemainSkor);
    simpanSkorKeCSV(pemainSkor);
    lanjut();
    menu_pemain();
}

//fungsi untuk menampilkan informasi tentang aplikasi
void tentang() {
    baca_tentang();
    lanjut();
    menu_utama();
}

//fungsi untuk melanjutkan ke menu berikutnya
void lanjut() {
    string lanjut;
    cout << "\nLanjutkan...";
    cin.ignore();
    getline(cin, lanjut);
}

//fungsi untuk menyimpan skor pemain ke file CSV
void simpanSkorKeCSV(const Skor& pemainSkor) {
    ofstream file("skor.csv", ios::app);
    if (file.is_open()) {
        file << pemainSkor.nama << "," << pemainSkor.id << "," << pemainSkor.nilai << "\n";
        file.close();
    } else {
        cout << "Gagal membuka file skor.csv\n";
    }
}

//fungsi untuk menghasilkan ID unik untuk pemain
string hasilkanIdUnik(const vector<string> &idTerpakai) {
    srand(time(0));
    string id;
    do {
        id = "ID" + to_string(rand() % 10000);
    } while (!idUnik(id, idTerpakai));
    return id;
}

//fungsi untuk memeriksa apakah ID yang dihasilkan unik
bool idUnik(const string &id, const vector<string> &idTerpakai) {
    return find(idTerpakai.begin(), idTerpakai.end(), id) == idTerpakai.end();
}

//fungsi untuk menampilkan papan skor
void papan_skor() {
    string pilihan;
    cout << "=== Papan Skor ===\n";
    cout << left << setw(20) << "Nama" << left << setw(10) << "ID" << left << setw(5) << "Nilai" << endl;
    for (const Skor& skor : papanSkor) {
        cout << left << setw(20) << skor.nama << left << setw(10) << skor.id << left << setw(5) << skor.nilai << endl;
    }
    cout << "\n1) Lihat 5 Skor Teratas\n"
         << "2) Lihat 5 Skor Terendah\n"
         << "3) Cari Nama\n"
         << "4) Kembali\n";
    cout << "Input: ";
    cin >> pilihan;
    system("cls");

    if (pilihan == "1") {
        cout << "5 Skor Teratas:\n";
        sort(papanSkor.begin(), papanSkor.end(), [](const Skor &a, const Skor &b) {
            return a.nilai > b.nilai;
        });
        for (int i = 0; i < min(5, static_cast<int>(papanSkor.size())); i++) {
            cout << papanSkor[i].nama << " - " << papanSkor[i].id << " - " << papanSkor[i].nilai << endl;
        }
    } else if (pilihan == "2") {
        cout << "5 Skor Terendah:\n";
        sort(papanSkor.begin(), papanSkor.end(), [](const Skor &a, const Skor &b) {
            return a.nilai < b.nilai;
        });
        for (int i = 0; i < min(5, static_cast<int>(papanSkor.size())); i++) {
            cout << papanSkor[i].nama << " - " << papanSkor[i].id << " - " << papanSkor[i].nilai << endl;
        }
    } else if (pilihan == "3") {
        string nama;
        cout << "Masukkan nama yang ingin dicari: ";
        cin >> nama;
        bool ditemukan = false;
        for (const Skor &skor : papanSkor) {
            if (skor.nama == nama) {
                cout << skor.nama << " - " << skor.id << " - " << skor.nilai << endl;
                ditemukan = true;
            }
        }
        if (!ditemukan) {
            cout << "Nama tidak ditemukan\n";
        }
    } else if (pilihan == "4") {
        menu_pemain();
    } else {
        cout << "Pilihan tidak ada\n";
        lanjut();
        papan_skor();
    }
    lanjut();
    menu_pemain();
}

//fungsi menu utama
void menu_utama() {
    system("cls");
    string pilihan;
    cout << "=== Selamat Datang di Kuis Edukasi ===\n"
         << "1) Admin\n"
         << "2) Pemain\n"
         << "3) Tentang\n"
         << "4) Keluar\n";
    cout << "Input: ";
    cin >> pilihan;
    system("cls");

    if (pilihan == "1") {
        admin();
    } else if (pilihan == "2") {
        menu_pemain();
    } else if (pilihan == "3") {
        tentang();
    } else if (pilihan == "4") {
        cout << "Terima kasih telah menggunakan aplikasi ini\n";
        exit(0);
    } else {
        cout << "Pilihan tidak ada\n";
        lanjut();
        menu_utama();
    }
}

//fungsi untuk memuat skor dari file CSV
void muatSkorDariCSV() {
    ifstream file("skor.csv");
    string line, nama, id;
    int nilai;

    if (file.is_open()) {
        while (getline(file, line)) {
            stringstream ss(line);
            getline(ss, nama, ',');
            getline(ss, id, ',');
            ss >> nilai;
            papanSkor.push_back({nama, id, nilai});
        }
        file.close();
    } else {
        cout << "Gagal membuka file skor.csv\n";
    }
}

//Fungsi utama
int main() {
    muatSkorDariCSV();
    menu_utama();
    return 0;
}