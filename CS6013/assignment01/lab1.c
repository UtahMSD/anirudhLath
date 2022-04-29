#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

/*********************************************************************
 *
 * These C functions use patterns and functionality often found in
 * operating system code. Your job is to implement them. Write some test
 * cases for each function ( stick them in a funciton called it xyzTests() or similar)
 * call your abcTests(), etc functions in main().
 *
 * Write your own tests for each function you are testing, then share/combine
 * tests with a classmate.  Try to come up with tests that will break people's code!
 * Easy tests don't catch many bugs!
 *
 * You may not use any global variables in your solution
 *
 *
 * You must compile in C mode (not C++).  If you compile from the commandline
 * run clang, not clang++. Submit your solution files on Canvas.
 *
 *********************************************************************/

void swap(unsigned char *a, unsigned char *b) {
    unsigned char temp = *a;
    *a = *b;
    *b = temp;
}

void printArray(unsigned char arr[], int c) {
    for (int i = 0; i < c; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}
void ascendingSort(unsigned char *byte, int count) {
    for (int i = 0; i < count - 1; ++i) {
        unsigned char idx_min = i;
        for (int j = i + 1; j < count; ++j) {
            if (byte[j] < byte[idx_min]) {
                idx_min = j;
            }
        }
        swap(&byte[i], &byte[idx_min]);
    }
}

void descendingSort(unsigned char *byte, int count) {
    for (int i = 0; i < count - 1; ++i) {
        unsigned char idx_max = i;
        for (int j = i + 1; j < count; ++j) {
            if (byte[j] > byte[idx_max]) {
                idx_max = j;
            }
        }
        swap(&byte[i], &byte[idx_max]);
    }
}


/*********************************************************************
 *
 * byte_sort()
 *
 * specification: byte_sort() treats its argument as a sequence of
 * 8 bytes, and returns a new unsigned long integer containing the
 * same bytes, sorted numerically, with the smaller-valued bytes in
 * the lower-order byte positions of the return value
 * 
 * EXAMPLE: byte_sort (0x0403deadbeef0201) returns 0xefdebead04030201
 * Ah, the joys of using bitwise operators!
 *
 * Hint: you may want to write helper functions for these two functions
 *
 *********************************************************************/

unsigned long byte_sort (unsigned long arg)
{
    unsigned char bytesArr[8];
    for (int i = 0; i < 8; ++i) {
        bytesArr[i] = (arg >> (i * 8)) & 0xFF;
    }
    ascendingSort(bytesArr, 8);
    unsigned long num = 0;

    for (int i = 0; i < 8; ++i) {
        unsigned long temp = bytesArr[i];
        num += (temp << (i * 8));
    }
  return num;
}

/*********************************************************************
 *
 * nibble_sort()
 *
 * specification: nibble_sort() treats its argument as a sequence of 16 4-bit
 * numbers, and returns a new unsigned long integer containing the same nibbles,
 * sorted numerically, with smaller-valued nibbles towards the "small end" of
 * the unsigned long value that you return
 *
 * the fact that nibbles and hex digits correspond should make it easy to
 * verify that your code is working correctly
 * 
 * EXAMPLE: nibble_sort (0x0403deadbeef0201) returns 0xfeeeddba43210000
 *
 *********************************************************************/

unsigned long nibble_sort (unsigned long arg)
{
    unsigned char bytesArr[16];
    for (int i = 0; i < 16; ++i) {
        bytesArr[i] = (arg >> (i * 4)) & 0xF; // mask last 4 bit and shift i * 4 bit every iteration
    }
    ascendingSort(bytesArr, 16);
    unsigned long num = 0;

    for (int i = 0; i < 16; ++i) {
        unsigned long temp = bytesArr[i];
        num += (temp << (i * 4));
    }
    return num;
}



/*********************************************************************
 *
 * name_list()
 *
 * specification: allocate and return a pointer to a linked list of
 * struct elts
 *
 * - the first element in the list should contain in its "val" field the first
 *   letter of your first name; the second element the second letter, etc.;
 *
 * - the last element of the linked list should contain in its "val" field
 *   the last letter of your first name and its "link" field should be a null
 *   pointer
 *
 * - each element must be dynamically allocated using a malloc() call
 * Note, that since we're using C, not C++ you can't use new/delete!
 * The analog to delete is the free() function
 *
 * - if any call to malloc() fails, your function must return NULL and must also
 *   free any heap memory that has been allocated so far; that is, it must not
 *   leak memory when allocation fails
 *
 *
 * Implement print_list and free_list which should do what you expect.
 * Printing or freeing a nullptr should do nothing
 * Note: free_list might be useful for error handling for name_list... 
 *********************************************************************/

struct elt {
  char val;
  struct elt *link;
};

void free_list(struct elt* head); /*so you can call free_list in name_list if you'd like*/
struct elt *name_list (void)
{
  char name[] = "Anirudh"; // Give a name

  // Initialise structs
  struct elt *current = NULL;
  struct elt *head = NULL;
  struct elt *next = NULL;

  // Allocate memory for head
  head = (struct elt*) malloc(sizeof(struct elt));

    if (head == NULL) {
        printf("malloc failed\n.");
        return NULL;
    }

    head->val = name[0]; // set first letter
    current = head;

    for (int i = 1; i < 8; ++i) {
        next = (struct elt*) malloc(sizeof(struct elt));
        if (next == NULL) {
            printf("malloc failed\n.");
            free_list(head);
            return NULL;
        }
        next->val = name[i]; // set letter
        current->link = next; // link next
        current = next; // set current to next to traverse forward
    }
    current->link = NULL;
    return head;
}

void print_list(struct elt* head){
    struct elt *currentNode = head;
    while(currentNode != NULL) {
        printf("%c", currentNode->val);
        currentNode = currentNode->link;
    }
}

void free_list(struct elt* head){
    struct elt *nextNode = NULL;
    struct elt *currentNode = head;

    while (currentNode != NULL) {
        nextNode = currentNode->link;
        free(currentNode);
        currentNode = nextNode;
    }
}


/*********************************************************************
 *
 * draw_me()
 *
 * this function creates a file called me.txt which contains an ASCII-art
 * picture of you (it does not need to be very big).
 * 
 * Use the C stdlib functions: fopen, fclose, fprintf, etc which live in stdio.h
 * don't use C++ iostreams
 *
 *
 *********************************************************************/

void draw_me (void)
{
    FILE *file;
    file = fopen("../file.txt", "w");
    fprintf(file, ",,,,,,,,,;;;;;ii111111t111ttttttttttttt1tttt1tt111111111ii1iiiii;;;;;;;;;;::::::::::::::::::1fG8@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@1iiiiiiiiiiiii11f@00000088888888\n"
                  ",,,,,,,,,,;;;iii111111tttttttttttttttttttttttttttttt1111111iiiii;;;;;;;;:::::::::G@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@Gft11111111111111tLG00000080888888\n"
                  ",,,,,,,,,,,:;;iiii1111tttttttttttttttttttttttttttt1tt111111iiiiii;;;;;;;;::::::::@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@GCLLffffffttttttttfiiiiiiiiiiiii11i\n"
                  "::,,,,,,,,,,:iiiii1111tttttttttttfffftftttttttttttttt1111111iiiii;i;;;;;:::::::::@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@8Ltt1tt0@GCCCCCLLLLLLffffLLiiiii;iiiiiiiiiii\n"
                  "8G:,,,,,,,,,,,iii11111ttttttfffffffffffffffttffftttttt1t11111iiiiii;;;;::::::::::@@@@@@@@@@@@@@@@@@@@@@8@@@@@1i;;;;;;;;;::;:1GGCCCCLLLLLLLLLL;ii;;;;;;;;;;;;iiii\n"
                  "888;:,,,,,,,,,,;iii111ttttttfffffffffffffftffftftttttttt1111111iiiii;;;;;;;::::::C@@@@@@@@@@GC@@@@t8@@@@@@@@@@@L0L1;;;;;;;;;;;1LLLLLLLLLLL;;;;;;;;;;;;;;;;;;;;;;\n"
                  "8888G:,,,,,,,,,,:iii111tttttftfffffffffffffffffftfttttttt1111iiiiiii;;;;;;;:::::::::t:1f@@@@@@@@@@@@@@@@@@@@@@@@@@G;;i;i;;;;;11111111t1;;;;;;;;;;;;;;;;;;;;;;;;;\n"
                  "888888;:,,,,,,,,,,ii1111tttfttfffffffffffffffffffffffttttt11111i1iii;;;;;;;;;::::;1f@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@8tG@@@Gi;;i11111111t::::;;;;;;;;;;;;;;;;;;;;;;\n"
                  "8888888G;:,,,,,,,,,i1111tttttfffffffffffffffffffffffftttttt11111iiii;;;;;;;;i::i@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@0Cii1iL1111111t;;:;:;;;:;;:;:;;:;;;;;;;;;;\n"
                  "@88888888;:,,,::,,,,;111tttttfffffffLffffffffffffffffffttttt1111iiiii;;;;;;i@C@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@000@@@t11111111:;;;;;;;;;;:::::;;::;;;;;;;\n"
                  "@@88888888G;::,::,::::t111ttttfffffffffffffffffffffffffttttt11111iiiii;;@f0@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@0L111111111;;;;;;::;;;;;;;::;;:;;;;;;;;\n"
                  "@@@888888888i;:::::::::1ttttttfffffffffLLffffffffffffftttttt11111iiii;LG0@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@GCt11111;:;;;;;;:;;::;;:::;;;;:;;;;;;\n"
                  "@@@@@@8888080Ci;::::::;;1tttttttffffffffffffffffffffffftttttt1111111f@@@@@@@@@@@@@@@@@800CttttffffLG08@@@@@@@@@@@@@@@@@@@@000Gt111i:;;;;;;;;;:;::;:;;:;;::::;;;;\n"
                  "@@@@@@@@@8800GG;;:::::;;;itttttttfffffffffLLLffffffffttttttt11111L@@@@@@@@@@@@@@0LL111ii;;;;;i;;;iii1tttfC8@@@@@@@@@@@@@@@@@@1111i;:;;::;:;;:;;::::::::::::::;;;\n"
                  "@@@@@@@@@@@Lfftt,,:::;;;;;;tttttttttfffffffffffffffffttttt11111@@@@0@@@@@@@@@@L1i;i;;;:::::,,,:::::;;ii11tttfC0@@@@@@@@@@@@@@@C1ii:;;;;;::;:::::::::::::::::;;;;\n"
                  "@@@@@@@@@@Lffft:::::;;;;;;;;ttttttffffffffffffffffffftttt11111t0@@@@@@@@@@@@0ti;;;;;::::,,,,,,,,,,,:::;;ii11tffC08@@@@@@@88811101::;;:;::::;::::::::::::::;;;;;;\n"
                  "@@@@@@@@@@ffftt::::::;;;;;i;;ittftfffffffffffffffffffttttt111t@@@@@@@@@@@@@8G1i;;::::::,::,,,,,..,,,::;;;;i11tffLG08@@@@@@@@111i1;;;;:::::::;;::::::::::::;;;;;;\n"
                  "@@@@@@@@@fffft::::::;;;;;;;iiiiftttffffffffffffffffffftttttt1111@@@@@@@@@@8C11i;;;:::::::,,,,,,.,,,,:::;;ii11ttffLCG0@@@@@@@@11i:;::::;;;::::::::::::::::;;;;;;;\n"
                  "@@@@@@@@8ffff1:::::;;;;;;;;iiiiitfffffffffffffffffffffffttttttL@@@C@@@@@@8L1iiii;;:::::,,,,,,,,,,,,,:::;;ii11ttfffLCG8@@@@@@@@00;;:;;;:;:::;:::::::::::;:;;;;iii\n"
                  "@@@@@@@@Lffff::ii;;;;;;;;;iiiiiiitfffffffffffLLLLfffLfffffftffLfLtt@@@@@G1iii11i;:,,,,,.,....,,,.,,,,,,::;ii11tfffLCG8@@@@@@@@@C;;;;:;;;;;::::::::::::;;iii111i1\n"
                  "0088@@@GLfff1;;iiii;;;;;;;iiiiii111ffftffffffLLLLLLLLLLLLffftfffftt@@@@ft1111ii1i:,,,,,,,......,,.,,.,,,::;ii1ttffCG08@@@@@@@@@@G;;;::;;;::::::::::::;;;ii1111tt\n"
                  "G000@@@Lffff;;iiiiii;;;;;iiiiii11111tffffffffLLLLLCCLLLLLLLLffffftt@@@Ltt1t000888888@@88C1t;:,,:,.....,,::;iii1tfLCGG0@@@@@@C@@@f;:::::::,:,,::::;;iitLLLfffLLLL\n"
                  "00G0@@LLfff1;;111i111i;;iiiiiii11111i11ttttffffffLfLffLffftttt1111ift1i11CGff11iiit0@@880GLti;:,,,:,::;f1tttt111tfCG008@@@C:tCft:,::::::::::::;;;;;;ii1f@@@@@@@8\n"
                  "G0@@@8fffff;;111111111iiiiiiiiiiii1ii;;;;;:;iii11i1111ittttt1tfff;;; ff1ti;;;;;::,.  iGGCftii;,,,;:;iL08@@@@@@@@888G000@@@:,,,,,,,,:::::::::;;;;;;;;;ii10@@@@@@@\n"
                  "tf@@@LLfff1;i11111111111iiiiiiiiiiiii;;;;;,,Lfffftffff;Lffftffftf;ttLLGCC1fCCf1i;:,:itf1::t1i:,.,;i1L00888@@@@@@@@@@800@@L,,,,,,,,::::::::::;;;;;;;;;;ii11ttfffL\n"
                  "08@@0LLfff;;ttttttttttttt1iiiii;..,:i;;;;:,:LLLffLLfLLiffff1fff11LCCfCGCLCC000888@80GLLC00Cf;:,.:;tC088;ittffftLG088888@@,,,,,,,,,:::::::::::;;;;;;;;;;iiiii1111\n"
                  "@@@@LLfffi;ittttttttttftft111i:   .,i;;;;,,1LLLL1LLLLftLLff;ffLG1i1GfCGCLfLG880G@@@@@0L00tfi;:::,;1ftLGfftttfC00GG000GG0:,,,,,,,,,,::::::::;;;;;;;;;iiiiiiii1111\n"
                  "@@@CLLfff;;ttttfftfffffffftti,    ,;f;;;;,,11iiiiiiiiiii;;ii;;CCLLt0:Lftt111i1fLfftfLf11tt1,:tiitC8GG0LG0@@@@@8088@8888CG@@@@1,,,,:::::::;;;;;;;;;;iiiiii1111111\n"
                  "@@8LLLffi;tffffffffffffLfff;:::  .;fi;;ti,:i;;;;;;;;;;;;;;;;:;fLtL0G1tt111i;;;;;;;;;;;i;;iffC,,:;CLt00CLLC@@@88@@@@8888@;@@@00:::::::::;;;;;;;;ii;iiiiii11111111\n"
                  "@@LLLLffiifffffffLLLLLLLLf;,.  .,;ti;;i0:,;;;;;;;;;;;;;;;;;;:;LtitCGCG1iii:::::::::,,,::;ftt,,,:;100LLGGGGGG088@@@8888@@@@@80::::::::;;;;;;;;;;iiiiii111111ttttt\n"
                  "@GLLLLfiitLLLLLLLLLLCCCCf;:....,:1f;;;;@:,ii;;;;ii;;;;;;;;;.@@0fit00L111ii:,,,,,,,,,,::;L0;:,.,,;tGLftttfffLLG000000888808@:::::::::;;;;;;;;iiiiiii111111ttttttt\n"
                  "@LLLLLfiiLLLLLCCCCCCCGG;,,....,;1Ciiii0;,,iiiiiiiiiii;;;;,@@@@@G1L@0f11iGfi::::,,,,,;ii1f;:,..,:;1Lfft111ttttfLLCCG008888@,::::::::;;;;;;;iiiiiiiii11111tttttttf\n"
                  "CLLLLLiifLCCCCCCCCGGGG:,.   .,:1Cf1Li1@::;1111111iii;;;; @@@@@@LLf@0L1t1t1iiii;;ifLLff:;;::,..,;;if00f1i;ii1tttffLCG088L0,,,::::::::;;;;;;;iiiiii1111ttttttffftf\n"
                  "LLLLLtiiCCCCCGGGGGGGf:,.     ,iGCCfCC8@::0GGGGGG0000088i@@@@@@@@fG@8Gttt1iiiiii;iiiit;:;1i::,,:itttLGCt1iii11ttfLLG008f;,::::::::::::::;;;;iiii11111ttttttffffff\n"
                  "CLLLLiiLCCGGGGGGG00i;,     .,iGGG08@C@0::@@@@@@@@@@@@@@@@@@@@@@@@@@@8Gtt1i;;;;;;;:::if0088Gt11tLG0CLGCLLC00GfffLLCCC0,:::::::::::::::;;;;;;;ii11111tttttffffffff\n"
                  "LLLLfi1CCGGGGGG00L1i...  ..:1GGGG0@@@@::i@@@@@@@@@@@@@@@@@@@@@@@@@@@@8Ct1iiii1ii;;:;ittfLCfC0888@@80Gtt11fLCGGG00088t::::::::::::::::::;;;;;ii11tttttttffffffffL\n"
                  "CLLLiiCCGGGGG000i1i,,:....:1GGGG0@@@@@::8@@@@@@@@@@@@@@@@@@@@@@@@@@@@@80tii1C@@8G0GLG0880880GG08880Gft111ttLCG00888@:::::::::::::::::::::;;;i11ttttttttfffffLfLL\n"
                  "LLLti1GGGGG0000fi;:::,,,,;tGGGGG@@@@@G::@@@@@@@@@88@L@@@@@@@@@@@@@@@@@@8f118@@@@@88G888C8@80G08@8@80GCfffffLCG0888@0;;;;;;;;;;;;:::::::::;;ii11ttttttffffffLLLLL\n"
                  "CLL1iGGGG00000t;;:,,,.  .,t00GG@@@@@@;::@@@@@@@@88@L@@@@@@@@@8@@@@@@@@@80ft8@@88@00000GGGfi;i;;f8@@8@@@8@8GGG088@@@iiiiii;iii;;;;;;;::::;;;i11tttttffffffffLLLLL\n"
                  "CCtitGGG000001;:,....    :88GG@@@@@@@::0@@@@@@@@@@0@@@@@@@@@@@8@@@@@@@@@0GLG8GfLLLGCGfG80GG0000000G08@@@@@@808@@@@Giiiiiiiiiiii;;;;;;:::;ii111ttttffffffLfLLLLLC\n"
                  "LL11GGG00000i::,,,,..    i@@@@@@@@@@8::@@@@@@@@@@@@@@@@@@@@@@@@@@8@@@@@@80CCCt1i1tttttti;1t1CfG08@@@@@@@@@@888@@@@iiiiiiiiiiiiiiiii;;;;:;ii111ttttffffffLLLCLLCC\n"
                  "Ct1f0000000::,,,,,,.    ,@@@@@@@@@@@;::@@@@@@@@@@@@@@@@@@@@@@@8 ,@@@@@@@@@800C1111ttttCGCLfffffLGG008888@@@8@@@@@iiiiiiiiiiiiiiiiiiii;:;;iii11tttfffffLLLLCCCCCC\n"
                  "C11000000C,,.......     8@@@@@@@@@@@::G@@@@@@@@@@@@@@@@@C,.    @@@00008@@@@@@80fttttLCLCG00000G0G0000088@@@@@@@iiiiiiiiiiiiiiiiiiiii;;:;;iii1ttffffLLLLLLLCCCCCC\n"
                  "t1L00000;,.....        ,@@@@@@@@@@@@::@@@@@@@@@@@@;            800000008@@@@@@@8GL1111ttCGGGG000000G00@@@@@@@@iiiiiiiiiiiiiiiiiiii1i;;;;iii11ttfffLLLLLCCCCCCCCC\n"
                  "110000i;::,,.          .@@@@@@@@@@@i::@@@@@0L,,::,,,.....  ..,.:LCG000008@@@@@@@801ii;i1LfffffLCG0008@@@@@@@0Lftt1iii11iiiiiiiiiii;;;;;;ii11ttffffLLLLCLLCCCCCCC\n"
                  "1L001;;;;::,.            @@@@@@@@@G:,,..      ..,,.. .,.  ... .:iLL00000088@@@@@@@8LGfftCLfLLCCLfG8@@@@@@@0tii11iii1111iii1111111111i:;ii111ttffffLLLLLLLCCCCCCC\n"
                  "t0f1i1i;:,..              .:,,:::::,,...     .,;,,,..,; .,..,,:;1Lf00GG00008@@@@@@@@8800G8C080@@@@@@@@@@t1t11iii;ii111i;ii111i1ii111i:iii11ttttffffLLLLLLLLCCCCC\n"
                  "1iiiii;:,...........,:::::,,,:;:;i1;,,,,......,;;;;:,:;:;;;;iii1fLfGGGGGGG0088@@@@@@@@@@@@@@@@@@@@@@@@80iiiiii;;;i111i;;iiiiiiiii1i1i;;iiii11ttttfffLLLLLLLCCCCC\n"
                  "iiii;::,,,,,,,,,,,,,.,,,,,,,,:;,:11;::::::::::;;i1tttttffft;,.L11fLLCCGGGGG000088@@@@@@@@@@@@@@@@@@@88@Li;;ii;:;iii11i;;;;;;;;;;;;;;i1it;;ii11ttttffffLLLLLLCCCC\n"
                  "ii;;;;::;;;;:..  ....,,,,,,,,,:..i;:;;iiii11fLLC:             .t1tf1CCGGCCCGG000088888@@@@@@@@@@@88888@i;::;;:::;iii;;::::::::::::;;;;iii11ii11ttttfffffLLLLCCCC\n"
                  "iiiii;;:,....   ..,,,,,::;::::;iffLCLfLLL:    .                Lt11tCCGGGCCGCCG0000000888888888888888@@;::,:::::::::::,,,,,,,,::::::::;i;;1itt11tftffffLLLLCCCCC\n"
                  "11ii:,,,,,,,,,.,,,,::;;ii11ttfCCCLfffttttt1    .                L11t:LC0GGGCCCCGGGG00000008888888888@@;:,..,,..,,,,,,,,,,,,,,,,,,,,:::;;;;;ii11ttttfffLLLLLLCCCC\n"
                  "i;;;:::;;;;:::::;;ii1LCG00000G000GGGCCLffffL;                    LtttLfC00GGCCCCCG000000000008888888@t:.....,...,.,,,..,,...,,,,,,,,:,;;;;;i;ii1ftffffLLLLLCCCCG\n"
                  "ii;:::::::,,,,::;i11t111iii1t11tffCGCCCLLCGG;                     Lt1,ffCG0GCCCCCCGG000000000808888@C:, ......  ,......,,...,,,,,,,,,,:;;;;i;iiiti1fLLLLLCCCCCCG\n"
                  ";;;;;::,.....,,,,:;::;;;;;;ii11111tttfLGGGG.                       Lttt11fCGCCCLLCCG0000GG00000888@G,,    . .    . .....,....,,,,,,,:::;;;;;;iiitiit1fLLCCCCCCCG\n"
                  ":::,,,.......,:;;;::::::::::;;iii11111fC000      .                  Lt;tii1fCCLLLCGGCCCCCCG0008888:,,            .  ........,.,,,,:::::;:1;;;iiitiiif11CCCCCCCCG\n"
                  "::::,,,,,....,::::::::::::::;;ii1111tfLG00t                          tLi1ii11fLLLCCCLfffLLCCG0088.,,.             .   ........,,,::::::i;1;;;ii11;iifLiiLCCCCCGG\n"
                  ";::::::,.   .,:;;;:::::;;;;;ii11tttfLL000                              C1tt111tt1tfffttttfLG000L...               .   ........,,,:;::::ii1;;iiitiiiifLfiitCGGGGG\n"
                  "::::;;;:,,;i1ttt1i;iiiiiii1111tttfLG0080GGf      .                       .fttt1tttfLLfffLLC00: .,        .         .  .....,..,,::;:::;iii1ii11tiiiifLffii1GGGGG\n"
                  "i1ii11i1tfLLft11tttffffL008C00Ct1i111tffLGf      ..                          fffLCCCCCL1.    ..   "
                  "                 ..  ....,,,,:::;;::;i1ifii1tt1iitLfffti1tGGGG");
    fclose(file);
}

int main() {
    printf("%lx\n", byte_sort(0x0403deadbeef0201));
    printf("%lx\n", nibble_sort(0x0403deadbeef0201));
    struct elt *test;
    test = name_list();
    print_list(test);
    free_list(test);
    draw_me();

}