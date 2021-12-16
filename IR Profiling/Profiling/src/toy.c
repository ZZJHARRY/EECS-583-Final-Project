int main()
{
    int x = 0;
    int y = 2;
    int z = 1; 
    int w = 2;

    while(x < 100000000){
        if (x >= 99999999) {
            y = 100;
            y = 101;
            y = 102;
            y = 103;
            y = 104;
            y = 105;
            y -= 1;
            y = z;
            y = 100;
            y = 101;
            y = 102;
            y = 103;
            y = 104;
            y = 105;
            y += 1;
            z = y;
            w = z;
            y = w;
        }
        else {
            z = y + z;
            
        }
        x += 1;
    }
}