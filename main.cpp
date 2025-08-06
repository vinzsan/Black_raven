#include <iostream>
#include <unistd.h>
#include <string.h>

class Stdout{
    public:
    void print(const char *str){
        while(*str){
            if(*str == '\n'){
                sleep(2);
            }
            putchar(*str++);
            fflush(stdout);
            usleep(90995);
        }
    }
};

int main(){
    const char *lyre = "Nama yang sama bertahan\n"
                        "Dalam ruangan hening\n"
                        "Tanpa suara bertahan\n"
                        "Tak bergeming\n"
                        "Terlalu lama bercanda\n"
                        "Kita tak terbiasa\n"
                        "Dengan celaka yang nyata\n"
                        "Diam tak berdaya\n"
                        "Namun aku bingung kenapa ku tak pergi\n"
                        "Aku bingung kalian masih di sini\n"
                        "Apa mungkin karena terlalu lama\n"
                        "Apa benar tuk berbagi derita\n"
                        "Mungkin nanti semua justru memburuk\n"
                        "Hati-hati namun terjatuh lagi\n"
                        "Tapi luka adalah niscaya\n"
                        "Kutanggung denganmu selama ku mampu\n"
                        "Selama ku mampu\n"
                        "Di kehidupan kedua (di kesempatan kedua)\n"
                        "S'moga kau tak terlalu keras kepala\n"
                        "Atau mungkin ini bukan yang pertama (ini bukan yang pertama)\n"
                        "Dan kita diberi kesempatan berubah\n"
                        "Kuyakin nyawa kita bertautan\n"
                        "Khatam berbagai cobaan\n"
                        "Selalu menertawakan ramalan bintang kartu tarot\n"
                        "Orang pintar pembaca nasib\n"
                        "Namun aku bingung kenapa ku tak pergi\n"
                        "Aku bingung kalian masih di sini\n"
                        "Apa mungkin karena terlalu lama\n"
                        "Apa benar tuk berbagi derita\n"
                        "Mungkin nanti semua justru memburuk\n"
                        "Hati-hati namun terjatuh lagi\n"
                        "Tapi luka adalah niscaya\n"
                        "Kutanggung denganmu selama ku mampu\n"
                        "Selama ku mampu\n"
                        "Selalu menertawakan ramalan bintang kartu tarot\n"
                        "Orang pintar pembaca nasib namun\n"
                        "Padamu kupercaya\n"
                        "Tak masuk logika\n"
                        "Padamu kupercaya\n"
                        "Tak masuk logika (tak masuk logika)\n"
                        "Padamu kupercaya (padamu kupercaya)\n"
                        "Tak masuk logika (tak masuk logika)\n"
                        "Padamu kupercaya (padamu kupercaya)\n"
                        "Tak masuk logika (tak masuk logika)\n"
                        "Padamu kupercaya\n"
                        "Tak masuk logika";
                        
    Stdout std;
    std.print(lyre);
    return 0;
}