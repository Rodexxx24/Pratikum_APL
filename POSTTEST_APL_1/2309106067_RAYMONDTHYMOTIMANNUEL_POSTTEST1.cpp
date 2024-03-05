#include <iostream>
#include <string>

using namespace std;

// Database untuk menyimpan username dan password
string username = "Raymond Thymotimannuel";
string password = "2309106067";
// Fungsi untuk login
bool login() {
    string input_username, input_password;
    int attempts = 0;

    // Memberikan 3 kesempatan untuk login
    while (attempts < 3) {
        cout << "Masukkan username: ";
        getline(cin, input_username);
        cout << "Masukkan password: ";
        getline(cin, input_password);

        if (input_username == username && input_password == password) {
            return true;
        } else {
            attempts++;
            cout << "Username atau password Anda salah. Kesempatan login tersisa: " << 3 - attempts << endl;
        }
    }

    // Jika melebihi 3 kali percobaan, berhenti program
    cout << "Username atau password Anda salah, silahkan coba lagi nanti!" << endl;
    return false;
}
// Fungsi untuk melakukan konversi
void konversi() {
    char choice;
    do {
        cout << "Pilih jenis inputan Anda\n";
        cout << "1. Km/jam\n";
        cout << "2. Cm/detik\n";
        cout << "3. Meter/detik\n";
        cout << "4. Mil/jam\n";
        cout << "Masukkan pilihan Anda: ";
        cin >> choice;

        double input_value;

        switch (choice) {
            case '1':
                cout << "Anda memilih Km/jam\n";
                cout << "Masukkan nilai dalam Km/jam: ";
                cin >> input_value;

                // Lakukan konversi Km/jam ke cm/detik, meter/detik, mil/jam
                cout << "Nilai dalam Cm/detik: " << input_value * 100000 / 3600 << endl;
                cout << "Nilai dalam Meter/detik: " << input_value * 1000 / 3600 << endl;
                cout << "Nilai dalam Mil/jam: " << input_value / 1.609 << endl;
                break;
            case '2':
                cout << "Anda memilih Cm/detik\n";
                cout << "Masukkan nilai dalam Cm/detik: ";
                cin >> input_value;

                // Lakukan konversi Cm/detik ke km/jam, meter/detik, mil/jam
                cout << "Nilai dalam Km/jam: " << input_value * 0.036 << endl;
                cout << "Nilai dalam Meter/detik: " << input_value / 100 << endl;
                cout << "Nilai dalam Mil/jam: " << input_value * 0.022 << endl;
                break;
            case '3':
                cout << "Anda memilih Meter/detik\n";
                cout << "Masukkan nilai dalam Meter/detik: ";
                cin >> input_value;

                // Lakukan konversi Meter/detik ke km/jam, cm/detik, mil/jam
                cout << "Nilai dalam Km/jam: " << input_value * 3.6 << endl;
                cout << "Nilai dalam Cm/detik: " << input_value * 100 << endl;
                cout << "Nilai dalam Mil/jam: " << input_value * 2.237 << endl;
                break;
            case '4':
                cout << "Anda memilih Mil/jam\n";
                cout << "Masukkan nilai dalam Mil/jam: ";
                cin >> input_value;

                // Lakukan konversi Mil/jam ke km/jam, cm/detik, meter/detik
                cout << "Nilai dalam Km/jam: " << input_value * 1.609 << endl;
                cout << "Nilai dalam Cm/detik: " << input_value * 44.704 << endl;
                cout << "Nilai dalam Meter/detik: " << input_value * 0.447 << endl;
                break;
            default:
                cout << "Opsi tidak terdaftar, coba lagi!" << endl;
                return; // Kembali ke program login
        }
        // Tanya user apakah ingin mencoba konversi lagi
        char again;
        cout << "Apakah Anda ingin mencoba konversi lagi? (ya/tidak): ";
        cin >> again;

        if (again != 'ya') {
            cout << "Terima kasih sudah mencoba program saya." << endl;
            break;
        }
    } while (true);
}
int main() {
    cout << "Selamat datang di program konversi!" << endl;

    // Melakukan login
    if (login()) {
        // Jika login berhasil, melakukan konversi
        konversi();
    }

    return 0;
}