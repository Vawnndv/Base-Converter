#include <iostream>
#include <string>
#include <string.h>
#include <math.h>
using namespace std;
// Nguyen Dinh Van_20127662 : Convert Decimal to Binary
void output(long long* binaryNum);
long long* dec_intergerToBinary(long long n);
void dec_double_32bit_ToBinary(double n);
void dec_double_64bit_ToBinary(double n);
// Luu Minh Phat_20127061 : Convert Binary to Decimal
bool checkBin(string strBin);
void Binary_32bits(string strBin, string& Bin_32);
void Binary_64bits(string strBin, string& Bin_64);
void PrintBin(string strb);
unsigned long long Convert_To_UnsignedInt(string Bin);
long long Convert_To_SingedInt(string Bin);
double Convert_To_Float(string Bin);

int main() {
    string Bin_32 = "";
    string Bin_64 = "";
    string strBin;
    int enter;
    cout << "--------------------------------------------------------------------------------" << endl;
    cout << "1. Convert Decimal to Binary!" << endl;
    cout << "2. Convert Binary to Decimal!" << endl;
    cout << "3. Exit!" << endl;
    cout << "Your choose: "; cin >> enter;
    cout << "-                            -" << endl;
    switch (enter) {
    case 1:
        //system("cls");
        long long n;
        double f;
        cout << "Enter integer: "; cin >> n;
        output(dec_intergerToBinary(n));
        cout << endl;
        cout << "Enter float: "; cin >> f;
        cout << "32 bit: ";
        dec_double_32bit_ToBinary(f);
        cout << endl;
        cout << "64 bit: ";
        dec_double_64bit_ToBinary(f);
        cout << endl;
        main();
        break;
    case 2:
        //system("cls");
        strBin = "";
        Bin_32 = "";
        Bin_64 = "";
        int type;
        cin.ignore();
        cout << "Enter an array binary: "; getline(cin, strBin);
        if (checkBin(strBin) == true) {
            if (strBin.size() > 32) Binary_64bits(strBin, Bin_64);
            else {

                cout << "Please choose type to contain: \n 1. 32 bits\n 2. 64 bits\n"; cin >> type;
                if (type == 1) {
                    Binary_32bits(strBin, Bin_32);
                    PrintBin(Bin_32);
                    cout << endl;
                    cout << "Dec (unsigned): " << Convert_To_UnsignedInt(strBin) << endl;
                    cout << "Dec (signed): " << Convert_To_SingedInt(strBin) << endl;
                    cout << "Float: " << Convert_To_Float(Bin_32) << endl;
                }
                else if (type == 2) {
                    Binary_64bits(strBin, Bin_64);
                    PrintBin(Bin_64);
                    cout << endl;
                    cout << "Dec (unsigned): " << Convert_To_UnsignedInt(strBin) << endl;
                    cout << "Dec (signed): " << Convert_To_SingedInt(strBin) << endl;
                    cout << "Float: " << Convert_To_Float(Bin_64) << endl;
                }
                else cout << "***Error***\n";
            }
        }
        else cout << "***Error***\n";
        main();
        break;
    case 3:
        return 0;
    default:
        main();
        break;
    }
    return 0;
}
// Nguyen Dinh Van_20127662: Convert Decimal to Binary
void output(long long* binaryNum) {
    cout << "8 bit: ";
    for (long long i = 56; i < 64; i++) {
        cout << binaryNum[i];
        if (i % 8 == 7)
            cout << " ";
    }
    cout << endl;
    cout << "32 bit: ";
    for (long long i = 33; i < 64; i++) {
        cout << binaryNum[i];
        if (i % 8 == 7)
            cout << " ";
    }
    cout << endl;
    cout << "64 bit: ";
    for (long long i = 0; i < 64; i++) {
        cout << binaryNum[i];
        if (i % 8 == 7)
            cout << " ";
    }
}
long long* dec_intergerToBinary(long long n) {
    long long* binaryNum = new long long[64];
    bool check_negative = 0;
    if (n < 0) {
        check_negative = 1;
        n = n * -1;
    }
    for (long long i = 0; i < 64; i++)
        if (!check_negative)
            binaryNum[i] = 0;
        else
            binaryNum[i] = 1;
    long long i = 63;
    long long vt;
    while (n > 0) {
        binaryNum[i] = n % 2;
        n = n / 2;
        i--;
    }
    for (long long j = 63; j > i; j--)
        if (binaryNum[j] == 1) {
            vt = j;
            break;
        }
    if (check_negative)
        for (long long j = vt - 1; j > i; j--)
            if (binaryNum[j] == 1)
                binaryNum[j] = 0;
            else
                binaryNum[j] = 1;
    return binaryNum;
}
void dec_double_32bit_ToBinary(double n) {
    long long mu = 0;
    double temp = abs(n);
    if (temp < 1)
        do {
            mu--;
            temp = abs(n) / pow(2, mu);
        } while (temp < 1);
        if (n < 0)
            n = temp * -1;
        else
            n = temp;
        long long phan_nguyen = abs((long long)(n));
        double phan_du = abs(n) - phan_nguyen;
        long long Dochinhxackep = (long long)(phan_du * pow(2, 23));
        long long dem = 22;
        long long* binary_phan_du = new long long[32];
        for (long long i = 0; i < 25; i++) {
            if (Dochinhxackep - pow(2, dem) >= 0) {
                binary_phan_du[i] = 1;
                Dochinhxackep -= pow(2, dem);
            }
            else
                binary_phan_du[i] = 0;
            dem--;
        }
        long long vt_nguyen, vt_du;
        long long* binary_phan_Nguyen = dec_intergerToBinary(phan_nguyen);
        for (long long i = 0; i < 64; i++)
            if (binary_phan_Nguyen[i] == 1) {
                vt_nguyen = i;
                break;
            }
        long long* binary_mu;
        if (mu == 0)
            binary_mu = dec_intergerToBinary(127 + 63 - vt_nguyen);
        else
            binary_mu = dec_intergerToBinary(127 + mu);
        for (long long i = 0; i < 64; i++)
            if (binary_mu[i] == 1) {
                vt_du = i;
                break;
            }
        if (n < 0)
            cout << "1";
        else
            cout << "0";
        cout << " ";
        for (long long i = 56; i < 64; i++)
            cout << binary_mu[i];
        cout << " ";
        dem = 0;
        for (long long i = vt_nguyen + 1; i < 64; i++) {
            cout << binary_phan_Nguyen[i];
            dem++;
            if (dem == 23)
                break;
        }
        for (long long i = 0; i < 23; i++) {
            cout << binary_phan_du[i];
            dem++;
            if (dem == 23)
                break;
        }
}
void dec_double_64bit_ToBinary(double n) {
    long long mu = 0;
    double temp = abs(n);
    if (temp < 1)
        do {
            mu--;
            temp = abs(n) / pow(2, mu);
        } while (temp < 1);
        if (n < 0)
            n = temp * -1;
        else
            n = temp;
        long long phan_nguyen = abs((long long)(n));
        double phan_du = abs(n) - phan_nguyen;
        long long Dochinhxackep = (long long)(phan_du * pow(2, 52));
        long long dem = 51;
        long long* binary_phan_du = new long long[52];
        for (long long i = 0; i < 52; i++) {
            if (Dochinhxackep - pow(2, dem) >= 0) {
                binary_phan_du[i] = 1;
                Dochinhxackep -= pow(2, dem);
            }
            else
                binary_phan_du[i] = 0;
            dem--;
        }
        long long vt_nguyen, vt_du;
        long long* binary_phan_Nguyen = dec_intergerToBinary(phan_nguyen);
        for (long long i = 0; i < 64; i++)
            if (binary_phan_Nguyen[i] == 1) {
                vt_nguyen = i;
                break;
            }
        long long* binary_mu;
        if (mu == 0)
            binary_mu = dec_intergerToBinary(1023 + 63 - vt_nguyen);
        else
            binary_mu = dec_intergerToBinary(1023 + mu);
        for (long long i = 0; i < 64; i++)
            if (binary_mu[i] == 1) {
                vt_du = i;
                break;
            }
        if (n < 0)
            cout << "1";
        else
            cout << "0";
        cout << " ";
        for (long long i = 53; i < 64; i++)
            cout << binary_mu[i];
        cout << " ";
        dem = 0;
        for (long long i = vt_nguyen + 1; i < 64; i++) {
            cout << binary_phan_Nguyen[i];
            dem++;
            if (dem == 52)
                break;
        }
        for (long long i = 0; i < 52; i++) {
            dem++;
            cout << binary_phan_du[i];
            if (dem == 52)
                break;
        }
}

// Luu Minh Phat_20127061 : Convert Binary to Decimal
bool checkBin(string strBin) {
    int check = 0;
    for (int i = 0; i < strBin.length(); i++) {
        if (strBin.compare(i, 1, "0") == 0 || strBin.compare(i, 1, "1") == 0) {
            check += 1;
        }
    }
    if (check == strBin.size()) return true;
    else return false;
}
void Binary_32bits(string strBin, string& Bin_32) {
    int n = 32 - strBin.size();
    while (n != 0) {
        Bin_32.append("0");
        n -= 1;
    }
    Bin_32.append(strBin);
}
void Binary_64bits(string strBin, string& Bin_64) {
    int n = 64 - strBin.size();
    int i = 0;
    while (n != 0) {
        Bin_64.append("0");
        n -= 1;
    }
    Bin_64.append(strBin);
}
void PrintBin(string strb) {
    int n = strb.size();
    for (int i = 0; i < n; i++) {
        cout << strb[i];
        if ((i + 1) % 4 == 0) cout << " ";
    }
}
unsigned long long Convert_To_UnsignedInt(string Bin) {
    int n = Bin.length();
    unsigned long long b = 1;
    unsigned long long dec = 0;
    for (int i = n - 1; i >= 0; i--) {
        if (Bin.compare(i, 1, "0") == 0) {
            b *= 2;
        }
        else {
            dec += b;
            b *= 2;
        }
    }
    return dec;
}
long long Convert_To_SingedInt(string Bin) {
    int sign = 1;
    int dec = 0;
    int n = Bin.length();
    int b = 1;
    if (Bin.compare(0, 1, "1") == 0) sign = -1;
    for (int i = n - 1; i >= 1; i--) {
        if (Bin.compare(i, 1, "0") == 0) {
            b *= 2;
        }
        else {
            dec += b;
            b *= 2;
        }
    }
    dec *= sign;
    return dec;
}
double Convert_To_Float(string Bin) {
    double S = 0;
    if (Bin.compare(0, 1, "1") == 0) S = -1;
    else S = 1;
    cout << "S (sign) = " << S << endl;

    double E = 1;
    double M = 1;
    int size = Bin.length();
    int sizeE;
    int sizeM;
    if (size == 32) sizeE = 8;
    else sizeE = 11;

    // Calculate Exponent
    double d = 0;
    double b = 1;
    for (int i = sizeE; i >= 1; i--) {
        if (Bin.compare(i, 1, "0") == 0) b *= 2;
        else {
            d += b;
            b *= 2;
        }
    }
    E = pow(2, d - 127);
    cout << "E (exponent) = " << E << endl;
    // Calculate Mantissa
    double bf = pow(2, -1);
    double df = 0.0;
    for (int i = sizeE + 1; i < size; i++) {
        if (Bin.compare(i, 1, "0") == 0) bf = bf * pow(2, -1);
        else {
            df += bf;
            bf = bf * pow(2, -1);
        }
    }
    M = 1 + df;
    cout << "M (mantissa) = " << M << endl;

    return S * E * M;
}