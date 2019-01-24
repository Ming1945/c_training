#include "base.h"
#include "unistd.h"
// template enums and structures

//Enumeration of Christmas tree elements
typedef enum {
    BALL,
    LED_CANDLE,
    STAR
} Tag;

//enumeration of different colors
typedef enum {
    RED,
    GREEN,
    YELLOW,
    GOLD,
    SILVER
} Color;

// structure representing a star
typedef struct{
    int corner_count;
} Star;

// structure representing a LED candle
typedef struct{
    bool on;
} LED_Candle;

// structure representing a Christmas ball
typedef struct{
    double radius;
    bool shiny;
} Ball;

//structure representing an element (tagged union). Might be a star, ball or candle.
typedef struct {
    Tag tag;
    Color color;
    union{
        Ball ball;
        LED_Candle candle;
        Star star;
    };
} Element;

struct Branch;

// structure representing a branch of a Christmas tree
typedef struct Branch{  
    bool dry;
    Element* element;
    struct Branch* left;
    struct Branch* right;
} Branch;

//Top of the Christmas tree
typedef struct{
    int height;
    Branch* branch;
} Tree;


// end template enums and structures


Element* new_ball(){
    Element* ball = xcalloc(1,sizeof(Ball)); //alocate 1 memory from struct Ball
    //todo
    ball->tag = BALL;
    ball->color = RED;
    ball->ball.radius = rand() % 9; //random radius from 0 till 8
    ball->ball.shiny = true; //the ball shines
    //end todo
    return ball;
}

Element* new_LED_candle(){
    Element* candle = xcalloc(1,sizeof(LED_Candle));
    //todo
    candle->tag = LED_CANDLE;
    candle->color = YELLOW;
    candle->candle.on = false;
    //end todo
    return candle;
}

Element* new_star(){
    Element* star = xcalloc(1,sizeof(Star));
    //todo
    star->tag = STAR;
    star->color = GOLD;
    star->star.corner_count = rand() % 9;
    //end todo
    return star;
}


Branch* new_branch(Branch* left, Branch* right){
    //todo
    Branch* branch = xcalloc(1,sizeof(Branch));
    int x = rand() % 3;
    Element* tagRandom;
    if (x == 0) tagRandom = new_ball();
    else if (x == 1) tagRandom = new_star();
    else tagRandom = new_LED_candle();
    branch->left = left;
    branch->right = right;
    branch->element = tagRandom; 
    branch->dry = false;
    //end todo
    return branch;
}

//todo
Branch* new_tree(int height,Branch* branch){
    if (height == 0) return NULL;
    else return new_branch(new_tree(height - 1,branch),new_tree(height - 1,branch));
}
//end todo

Tree* new_xmas_tree(int height){
    //todo
    Tree* tree = xcalloc(1,sizeof(Tree));
    tree->height = height;
    tree->branch = new_tree(height , 0);
    //end todo
    return tree;
}

//todo

void free_branch(Branch* branch){
    if(branch != NULL){
        free_branch(branch->left);
        free_branch(branch->right);
        free(branch->element);
        free(branch);
    }
}

//frees the by the tree allocated memory.
void free_tree(Tree* tree){
    //todo
    if(tree != NULL) {
        free_branch(tree->branch);
        free(tree);
    }
    //end todo
}


int rec_depth_count(Branch* branch, int depth, int act_depth){
    if(branch == NULL){
        return 0;
    }
    if(act_depth == depth){
        return 1;
    }
    
    return rec_depth_count(branch->left, depth, act_depth + 1) + rec_depth_count(branch->right, depth, act_depth + 1);
}


int get_count_of_branches_for_depth(Tree* tree, int depth){

    int count = 0;
    if(tree == NULL || depth >= tree->height){
        return 0;
    }
    count = rec_depth_count(tree->branch, depth, 0);

    return count;
}

//template code
Branch* get_branch(Tree* tree, int depth, int index){
    int branches_in_depth = 0;
    if(tree == NULL || depth >= tree->height || index > (branches_in_depth = get_count_of_branches_for_depth(tree, depth))){
        return NULL;
    }
    Branch* b = tree->branch;
    int cur_depth = 0;
    while(cur_depth < depth && b ){ 
        if(index % 2 == 0){
            b = b->left;
        }
        else{
            b = b->right;
        }
        index = index >> 1;
        cur_depth ++;   
    }
    return b;
}

void print_stars(int count){
    String star[] = {
    "     /\\     ",
    "____/**\\____",
    "\\**********/",
    " \\********/ ",
    " /d*.**.*b\\ ",
    "/.-     `-.\\"
    };

    for(int i = 0; i < 6; i++){
        for(int j = 0; j < count; j++){
            printf("%s\t", star[i]);
        }
        printf("\n");
    }
    printf("\n\n\n");
}

char print_element(Element* element){
    char c = '#';           
    switch (element->tag){  
        case BALL:
            if(element->ball.radius > 4.0){
                c = 'O';
            }else{
                c = 'o';
            }
        break;
        case LED_CANDLE:
            if (element->candle.on){
                c = 'I';
            }else{
                c = 'i';
            }
        break;
        case STAR:
            if(element->star.corner_count < 5){
                c = '+';
            }else{
                c = '*';
            }           
            break;
    }
    return c;
}


void print_xmas_tree(Tree* tree){
    if(!tree){
        return;
    }
    int max_width = get_count_of_branches_for_depth(tree, tree->height - 1);
    String corner = "/ \\";
    for(int i = 1; i< ((max_width ) * 3) / 2 + 1; i++){
            printf(" ");
    }
    printf("%s\n", corner);
    
    if(tree != NULL && tree->height >= 0){
        for(int i = 0; i< tree->height; i++){
            
            int count_of_spaces = ((max_width - get_count_of_branches_for_depth(tree, i) ) * 3) / 2 + 1;
            for(int j = 0; j < count_of_spaces ; j++){
                printf(" ");
            }
            printf("/");
            for(int j = 0; j < get_count_of_branches_for_depth(tree, i); j++){
                Branch* b = get_branch(tree, i, j);
                
                if(b && b->element){
                    char c = print_element(b->element);
                    printf(" %c ", c);
                }else{
                    printf("( )");
                }
            }
            
            printf("\\\n");
            
            for(int j = 0; j < count_of_spaces - 1; j++){
                printf(" ");
            }
            printf("/");
            for(int j = 0; j < get_count_of_branches_for_depth(tree, i); j++){
                printf("   ");
            }
            printf("  ");
            printf("\\\n");
        }
    }

    String trunc = "|  |";
    
    //prints trunc
    for(int j = 0; j< 3; j++){
        for(int i = 0; i< ((max_width -1) * 3) / 2 + 1; i++){
            printf(" ");
        }
        printf("%s\n", trunc);
    }
}


void light_candles_rec(Branch* b, bool on){
    if(b == NULL){
        return;
    }
    if(b->element){
        if(b->element->tag == LED_CANDLE){
            b->element->candle.on = on;
        }
    }
    light_candles_rec(b->left, on);
    light_candles_rec(b->right, on);
}

void light_candles(Tree* tree, bool on){
    if(!tree){
        return;
    }
    light_candles_rec(tree->branch, on);
}
//end template code

//todo

//todo: Tree stats
int tagCounter(Branch* branch , Tag tag) {
    int tag_count = 0;
    if (branch == NULL) return 0;
    if (branch->element->tag == tag) tag_count++;
    return tag_count + tagCounter(branch->left , tag) + tagCounter(branch->right , tag) ;
}


void print_tree_stats(Tree* tree){
    printf("Tree Statistics : \n");
    printf("Stars : %d\n" , tagCounter(tree->branch , STAR));
    printf("Balls : %d\n" , tagCounter(tree->branch , BALL));
    printf("Candles : %d\n" , tagCounter(tree->branch , LED_CANDLE));
}



int branchCounter(Branch* branch) {
    if (branch == NULL) return 0;
    return 1 + branchCounter(branch->left) + branchCounter(branch->right);
}


int dryCounter (Branch* branch) {
    int dry_counter = 0;
    if (branch == NULL) return 0;
    if (branch->dry == true) dry_counter++;
    return dry_counter + dryCounter(branch->left) + dryCounter(branch->right);
}

void dryPercentage(Branch* branch) {

    if (branch == NULL) return;
    dryPercentage(branch->left);
    dryPercentage(branch->right);

    if (branch->left == NULL && branch->right == NULL) {
        if (i_rnd(100) < 25) { 
            branch->dry = true;
        }
    }

    else if (branch->right && branch->left) {
        if ((branch->left->dry == true) ^ (branch->right->dry == true)) { 
            if (i_rnd(100) < 50) { 
                branch->dry = true;
            }
        }
        if (branch->left->dry == true && branch->right->dry == true) {
            if (i_rnd(100) < 75) { 
                branch->dry = true;
            }
        }
        else {
            if (i_rnd(100) < 10) { 
                branch->dry = true;
            }
        }
    }

}


int dryDays(Tree* tree) {
    int days = 0;
    if (tree == NULL) return 0;
    if (dryCounter(tree->branch) == branchCounter(tree->branch)) return 0;
    Tree* drying_tree = tree;
    while (dryCounter(drying_tree->branch) != branchCounter(drying_tree->branch)) {
        days++;
        dryPercentage(drying_tree->branch);
    }
    return days;
}

void dryStatisticsTree(Tree* tree) {
    int i;
    int average_days = 0;
    int days = 0;
    for (i = 0; i < 100; i++) {
        Tree* tree1 = new_xmas_tree(tree->height);
        days = days + dryDays(tree1);
        free_tree(tree1);
    }
    average_days = days / 100;
    printf("Tree height: %d\n", tree->height);
    printf("Average days before tree dried up (out of 100): %d\n", average_days);
}

void dry_stats(void) {
    Tree* tree5 = new_xmas_tree(5);
    Tree* tree6 = new_xmas_tree(6);
    Tree* tree7 = new_xmas_tree(7);
    Tree* tree8 = new_xmas_tree(8);
    Tree* tree9 = new_xmas_tree(9);
    Tree* tree10 = new_xmas_tree(10);

    printf("Dry out statistics: \n");
    dryStatisticsTree(tree5);
    dryStatisticsTree(tree6);
    dryStatisticsTree(tree7);
    dryStatisticsTree(tree8);
    dryStatisticsTree(tree9);
    dryStatisticsTree(tree10);
    
    free_tree(tree5);
    free_tree(tree6);
    free_tree(tree7);
    free_tree(tree8);
    free_tree(tree9);
    free_tree(tree10);
}









int main(void){
    base_init();
    base_set_memory_check(true);
    print_stars(6);

    Tree* tree = new_xmas_tree(5);
    
    print_xmas_tree(tree);
    //print stats:
    print_tree_stats(tree);
    
    //evaluate dry out method
    dry_stats();
    
    int c;
    bool candles_on = false;
    while((c = getchar())!= 'q'){
        if(c == 'c'){
            candles_on = ! candles_on;
            light_candles(tree, candles_on);
            print_xmas_tree(tree);
        }
        print_tree_stats(tree);
    }
    
    free_tree(tree);

    
    return 0;
}


/*
AUFGABE F 


*/