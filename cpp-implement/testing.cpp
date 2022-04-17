#include <stdio.h>
#include "Hemex.cpp"

int main(int argc, char *argv[])
{
    Hemex::Hemex hmx;
    hmx.setText(" for {len}");

    hmx.addLexer("PUBLIC",[](Hemex::Hemex hmx) -> void{
        printf("Çalıştı\n");
    });

    hmx.gather("PUBLIC");

    printf("Derleme Başarılı!\n");
}