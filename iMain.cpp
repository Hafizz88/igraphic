# include "iGraphics.h"  
#include <iostream>
using namespace std;                        ///total_pts is actually total things



// Enumeration for different modes and tools
typedef enum {
    HOME_SCREEN = 0,
    CREATE_PICTURE = 1,
    EDIT_PICTURE = 2,
    LOAD_TO_VIEW = 3,
    VIEW = 4
} Mode;

typedef enum {
    FREE_DRAW = 0,
    PRECISE_DRAW_ERASE = 1,
    ERASER = 2,
    SMALL_BRUSH_ERASER = 3,
    MEDIUM_BRUSH_ERASER = 4,
    LARGE_BRUSH_ERASER = 5,
    XL_BRUSH_ERASER = 6,
    TEXT_BOX = 7,
    SAVE_FILE_ERROR = 8,
    PAINTING_SAVED = 9,
    READ_PAINTING_ERROR = 10,
    PAINTING_LOADED = 11,
    CIRCLE_TOOL = 12,
    RECTANGLE_TOOL = 13,
    FILLED_RECTANGLE_TOOL = 14,
    ELLIPSE_TOOL = 15,
    FILLED_ELLIPSE_TOOL = 16,
    LINE_TOOL = 17,
    POLYGON_TOOL = 18,
    FILLED_POLYGON_TOOL = 19,
    END_LINE = 20
} Tool;

int mode, tool;                                 // mode 0 for homescreen        //tool 0 for Free draw                          7 rectangle tool    8 filled rectangle tool
int total_pts;                                 // 1 for creating picture              //tool 1 for precise draw and erase       6 circle tool
int curr_r, curr_g, curr_b;               // 2 for editing picture                  //tool 2 for free eraser                      5 halt drawing state for save prompt
       //current rgb values                // 3 for load to view                 // tool 3 for textBox select coord      4 for textBox edit text
                                                  // 4 to view                                    // 9 for ellipse    // 10 for filled ellipse    // 11 poly  // 12 filled poly   // 13 line // 14 end line

int showPrompt, promptMsgNo, threeSecCnt, showSavePrompt, save_cnt, circleCnt, filledCircleCnt, rectangleCnt, filledRectCnt,
        ellipseCnt, filledEllipseCnt, lineCnt, polyCnt, filledPolyCnt;

int curr_pts_size, showPallete, textsAtCnt, len, showingMoreIcons;

char promptMsg[][100] ={"Free Draw Tool Selected", "Precise Draw Tool Selected", "Eraser Tool Selected",
                                        "Small Brush/Eraser Selected", "Medium Brush/Eraser Selected", "Large Brush/Eraser Selected",
                                        "XL Brush/Eraser Selected", "Text Box Selected", "Type text. Hit Enter to end", "Save File could not be written",
                                         "Painting Saved Successfully", "Error Reading Painting Data", "Painting Loaded Successfully",
                                         "Circle Tool Selected", "Rectangle Tool Selected", "Filled Rectangle Tool Selected",
                                         "Ellipse Tool Selected", "Filled Ellipse Tool Selected", "Line Tool Selected", "Click on end point", "Polygon Tool. Right Click to add Vertex",
                                         "Vertex Selected. Left click for final Vertex", "Filled Polygon Tool. Right Click to add Vertex"};

char save_filename[100], save_names[100][100];

typedef struct {                // pts

    int x, y, r, g, b, size;

} pts;

typedef struct {                // textbox

int r,g,b, x, y;
char text[100];

} textBox;

typedef struct {                // circle

int x, y, r, g, b, size;

} circle;

typedef struct {                // filledCircle

int x, y, r, g, b, size;

} filledCircle;

typedef struct {                // rectangle

int x, y, dx, dy, r, g, b;

} rectangle;

typedef struct {                // filledRect

int x, y, dx, dy, r, g, b;

} filledRect;

typedef struct {                // ellipse

int x, y, da, db, r, g, b;

} ellipse;

typedef struct {                // filledEllipse

int x, y, da, db, r, g, b;

} filledEllipse;

typedef struct {                // line

int x1, y1, x2, y2, r, g, b;

} line;

typedef struct {                // poly

double x[100], y[100];
int n=0, r, g, b;

} poly;

typedef struct {                // filledPoly

double x[100], y[100];
int n=0, r, g, b;

} filledPoly;

pts * PointsArr= (pts *) malloc(9999999 * sizeof(pts));

textBox * textBoxArr= (textBox *) malloc (20 * sizeof (textBox));
int * textsAt = (int *) malloc (20* sizeof (int));

circle * circleArr = (circle *) malloc (100* sizeof(circle));
int * circlesAt = (int *) malloc (100* sizeof (int));

filledCircle * filledCircleArr = (filledCircle *) malloc (100* sizeof(filledCircle));
int * filledCirclesAt = (int *) malloc (100 * sizeof(int));

rectangle * rectangleArr = (rectangle *) malloc (100* sizeof(rectangle));
int * rectanglesAt = (int *) malloc (100* sizeof(int));

filledRect * filledRectArr = (filledRect *) malloc (100 * sizeof(filledRect));
int * filledRectsAt = (int *) malloc (100* sizeof(int));

ellipse * ellipseArr = (ellipse *) malloc (100* sizeof(ellipse));
int *ellipsesAt = (int *) malloc (100* sizeof(int));

filledEllipse * filledEllipseArr = (filledEllipse *) malloc (100 * sizeof(filledEllipse));
int *filledEllipsesAt = (int *) malloc (100 * sizeof(int));

line * lineArr = (line *) malloc (100 * sizeof(line));
int * linesAt = (int *) malloc (100 * sizeof(int));

poly * polyArr = (poly *) malloc (50 * sizeof(poly));
int * polysAt = (int *) malloc (50 * sizeof(int));

filledPoly * filledPolyArr = (filledPoly *) malloc (50 * sizeof(filledPoly));
int * filledPolysAt = (int *) malloc (50 * sizeof(int));


void SaveFile(char save_filename[]) {

    promptMsgNo=10;

    FILE * to_write = fopen (save_filename, "wb");

    if (to_write==NULL) promptMsgNo=9;

    if (fwrite(&total_pts, sizeof(int), 1, to_write)!=1)  promptMsgNo=9;

    if (fwrite(&textsAtCnt, sizeof(int), 1, to_write)!=1) promptMsgNo=9;

    if (fwrite(&circleCnt, sizeof(int), 1, to_write)!=1) promptMsgNo=9;

    if (fwrite(&filledCircleCnt, sizeof(int), 1, to_write)!=1) promptMsgNo=9;

    if (fwrite(&rectangleCnt, sizeof(int), 1, to_write)!=1) promptMsgNo=9;

    if (fwrite(&filledRectCnt, sizeof(int), 1, to_write)!=1) promptMsgNo=9;

    if (fwrite(&ellipseCnt, sizeof(int), 1, to_write)!=1) promptMsgNo=9;

    if (fwrite(&filledEllipseCnt, sizeof(int), 1, to_write)!=1) promptMsgNo=9;

    if (fwrite(&lineCnt, sizeof(int), 1, to_write)!=1) promptMsgNo=9;

    if (fwrite(&polyCnt, sizeof(int), 1, to_write)!=1) promptMsgNo=9;

    if (fwrite(&filledPolyCnt, sizeof(int), 1, to_write)!=1) promptMsgNo=9;

    if (fwrite(textsAt, sizeof(int), textsAtCnt, to_write)!=textsAtCnt) promptMsgNo=9;

    if (fwrite(circlesAt, sizeof(int), circleCnt, to_write)!=circleCnt) promptMsgNo=9;

    if (fwrite(filledCirclesAt, sizeof(int), filledCircleCnt, to_write)!=filledCircleCnt) promptMsgNo=9;

    if (fwrite(rectanglesAt, sizeof(int), rectangleCnt, to_write)!=rectangleCnt) promptMsgNo=9;

    if (fwrite(filledRectsAt, sizeof(int), filledRectCnt, to_write)!=filledRectCnt) promptMsgNo=9;

    if (fwrite(ellipsesAt, sizeof(int), ellipseCnt, to_write)!=ellipseCnt) promptMsgNo=9;

    if (fwrite(filledEllipsesAt, sizeof(int), filledEllipseCnt, to_write)!=filledEllipseCnt) promptMsgNo=9;

    if (fwrite(linesAt, sizeof(int), lineCnt, to_write)!=lineCnt) promptMsgNo=9;

    if (fwrite(polysAt, sizeof(int), polyCnt, to_write)!=polyCnt) promptMsgNo=9;

    if (fwrite(filledPolysAt, sizeof(int), filledPolyCnt, to_write)!=filledPolyCnt) promptMsgNo=9;

    if (fwrite(PointsArr, sizeof(pts), total_pts, to_write)!=total_pts) promptMsgNo=9;

    if (fwrite(textBoxArr, sizeof(textBox), textsAtCnt, to_write)!=textsAtCnt)  promptMsgNo=9;

    if (fwrite(circleArr, sizeof(circle), circleCnt, to_write)!=circleCnt)  promptMsgNo=9;

    if (fwrite(filledCircleArr, sizeof(filledCircle), filledCircleCnt, to_write)!=filledCircleCnt)  promptMsgNo=9;

    if (fwrite(rectangleArr, sizeof(rectangle), rectangleCnt, to_write)!=rectangleCnt)  promptMsgNo=9;

    if (fwrite(filledRectArr, sizeof(filledRect), filledRectCnt, to_write)!=filledRectCnt)  promptMsgNo=9;

    if (fwrite(ellipseArr, sizeof(ellipse), ellipseCnt, to_write)!=ellipseCnt)  promptMsgNo=9;

    if (fwrite(filledEllipseArr, sizeof(filledEllipse), filledEllipseCnt, to_write)!=filledEllipseCnt)  promptMsgNo=9;

    if (fwrite(lineArr, sizeof(line), lineCnt, to_write)!=lineCnt)  promptMsgNo=9;

    if (fwrite(polyArr, sizeof(poly), polyCnt, to_write)!=polyCnt)  promptMsgNo=9;

    if (fwrite(filledPolyArr, sizeof(filledPoly), filledPolyCnt, to_write)!=filledPolyCnt)  promptMsgNo=9;


    if(fclose(to_write)==EOF) promptMsgNo=9; 


    // Close the file
    fclose(to_write);
}
    void readList() {
FILE * save_list = fopen("saves", "a+");                            // now adding painting name to the list of saves, if it doesnt already exist

     if (save_list==NULL) promptMsgNo=9;

    char sfn_var [100];                 // a var str to store save_filename

    strcpy(sfn_var, save_filename);
    strcat(sfn_var, "\n");              //     save_filename should not be changed because if \n added to it,
                                                //      it will still have \n when next time save is called, filename cant have a \n in it

    bool exists=false;

    while (!feof(save_list)) {

        char read[100]; fgets(read, 100, save_list);

        if(!strcmp(read, sfn_var)){                        // if matching case found
            exists=true;
            break;
            }
    }                                                            // returns 0 if a matching case found

    if (!exists) {
        fputs(save_filename, save_list);
        fputc('\n', save_list);
    }

    fclose(save_list);

    showPrompt=1;

}



void LoadFile(char save_name[]) {

    promptMsgNo=12;

    FILE * from_save = fopen(save_name, "rb");

    if (from_save==NULL)
    showPrompt=1, promptMsgNo=11, mode=1;           // redirect to creation page if save file not read correctly

    if (fread(&total_pts, sizeof(int), 1, from_save) !=1)  showPrompt=1, promptMsgNo=11, mode=1;

    if (fread(&textsAtCnt, sizeof(int), 1, from_save)!=1)  showPrompt=1, promptMsgNo=11, mode=1;

    if (fread(&circleCnt, sizeof(int), 1, from_save)!=1)  showPrompt=1, promptMsgNo=11, mode=1;

    if (fread(&filledCircleCnt, sizeof(int), 1, from_save)!=1)  showPrompt=1, promptMsgNo=11, mode=1;

    if (fread(&rectangleCnt, sizeof(int), 1, from_save)!=1)  showPrompt=1, promptMsgNo=11, mode=1;

    if (fread(&filledRectCnt, sizeof(int), 1, from_save)!=1)  showPrompt=1, promptMsgNo=11, mode=1;

    if (fread(&ellipseCnt, sizeof(int), 1, from_save)!=1)  showPrompt=1, promptMsgNo=11, mode=1;

    if (fread(&filledEllipseCnt, sizeof(int), 1, from_save)!=1)  showPrompt=1, promptMsgNo=11, mode=1;

    if (fread(&lineCnt, sizeof(int), 1, from_save)!=1)  showPrompt=1, promptMsgNo=11, mode=1;

    if (fread(&polyCnt, sizeof(int), 1, from_save)!=1)  showPrompt=1, promptMsgNo=11, mode=1;

    if (fread(&filledPolyCnt, sizeof(int), 1, from_save)!=1)  showPrompt=1, promptMsgNo=11, mode=1;

    if (fread(textsAt, sizeof(int), textsAtCnt, from_save)!= textsAtCnt) showPrompt=1, promptMsgNo=11, mode=1;

    if (fread(circlesAt, sizeof(int), circleCnt, from_save)!= circleCnt) showPrompt=1, promptMsgNo=11, mode=1;

    if (fread(filledCirclesAt, sizeof(int), filledCircleCnt, from_save)!= filledCircleCnt) showPrompt=1, promptMsgNo=11, mode=1;

    if (fread(rectanglesAt, sizeof(int), rectangleCnt, from_save)!= rectangleCnt) showPrompt=1, promptMsgNo=11, mode=1;

    if (fread(filledRectsAt, sizeof(int), filledRectCnt, from_save)!= filledRectCnt) showPrompt=1, promptMsgNo=11, mode=1;

    if (fread(ellipsesAt, sizeof(int), ellipseCnt, from_save)!= ellipseCnt) showPrompt=1, promptMsgNo=11, mode=1;

    if (fread(filledEllipsesAt, sizeof(int), filledEllipseCnt, from_save)!= filledEllipseCnt) showPrompt=1, promptMsgNo=11, mode=1;

    if (fread(linesAt, sizeof(int), lineCnt, from_save)!= lineCnt) showPrompt=1, promptMsgNo=11, mode=1;

    if (fread(polysAt, sizeof(int), polyCnt, from_save)!= polyCnt) showPrompt=1, promptMsgNo=11, mode=1;

    if (fread(filledPolysAt, sizeof(int), filledPolyCnt, from_save)!= filledPolyCnt) showPrompt=1, promptMsgNo=11, mode=1;

    if(fread(PointsArr, sizeof(pts), total_pts, from_save)!=total_pts) showPrompt=1, promptMsgNo=11, mode=1;

    if(fread(textBoxArr, sizeof(textBox), textsAtCnt, from_save)!=textsAtCnt) showPrompt=1, promptMsgNo=11, mode=1;

    if(fread(circleArr, sizeof(circle), circleCnt, from_save)!=circleCnt) showPrompt=1, promptMsgNo=11, mode=1;

    if(fread(filledCircleArr, sizeof(filledCircle), filledCircleCnt, from_save)!=filledCircleCnt) showPrompt=1, promptMsgNo=11, mode=1;

    if(fread(rectangleArr, sizeof(rectangle), rectangleCnt, from_save)!=rectangleCnt) showPrompt=1, promptMsgNo=11, mode=1;

    if(fread(filledRectArr, sizeof(filledRect), filledRectCnt, from_save)!=filledRectCnt) showPrompt=1, promptMsgNo=11, mode=1;

    if(fread(ellipseArr, sizeof(ellipse), ellipseCnt, from_save)!=ellipseCnt) showPrompt=1, promptMsgNo=11, mode=1;

    if(fread(filledEllipseArr, sizeof(filledEllipse), filledEllipseCnt, from_save)!= filledEllipseCnt) showPrompt=1, promptMsgNo=11, mode=1;

    if(fread(lineArr, sizeof(line), lineCnt, from_save)!= lineCnt) showPrompt=1, promptMsgNo=11, mode=1;

    if(fread(polyArr, sizeof(poly), polyCnt, from_save)!= polyCnt) showPrompt=1, promptMsgNo=11, mode=1;

    if(fread(filledPolyArr, sizeof(filledPoly), filledPolyCnt, from_save)!= filledPolyCnt) showPrompt=1, promptMsgNo=11, mode=1;

    if(fclose(from_save)==EOF) showPrompt=1, promptMsgNo=11, mode=1;

    showPrompt=1;

}



   void threeSec() {

    threeSecCnt++;

      if (threeSecCnt==3) iPauseTimer(0), showPrompt=0;

}

   
   void ReadList() {

        FILE * save_list= fopen("saves", "r");
        if (save_list==NULL) {mode=1, showPrompt=1, promptMsgNo=11; return;}

            while (!feof(save_list)) {                        // if no prob

                char c=fgetc(save_list);
                if (c=='\n') save_cnt++;

            }

        rewind(save_list);

        for (int i=0; i<save_cnt; i++) {

            fgets(save_names[i], 100, save_list);

            save_names[i][strlen(save_names[i])-1]='\0';      // Adding null char to  end of each filename read

          }

          fclose(save_list);


}
void init();
void freeMem();
void erase();


void displayThings() {
    // Draw all points, shapes, and text on the canvas
    for (int i = 0, p = 0, q = 0, z = 0, s = 0, t = 0, u = 0, v = 0, w = 0, e = 0, f = 0; i < total_pts; i++) {
        // Draw text boxes
        if (i == textsAt[p]) {
            iSetColor(textBoxArr[p].r, textBoxArr[p].g, textBoxArr[p].b);
            iText(textBoxArr[p].x, textBoxArr[p].y, textBoxArr[p].text, GLUT_BITMAP_HELVETICA_12);
            p++;
        }
        // Draw circles
        else if (i == circlesAt[q]) {
            iSetColor(circleArr[q].r, circleArr[q].g, circleArr[q].b);
            iCircle(circleArr[q].x, circleArr[q].y, circleArr[q].size, 1000);
            q++;
        }
        // Draw filled circles
        else if (i == filledCirclesAt[z]) {
            iSetColor(filledCircleArr[z].r, filledCircleArr[z].g, filledCircleArr[z].b);
            iFilledCircle(filledCircleArr[z].x, filledCircleArr[z].y, filledCircleArr[z].size, 1000);
            z++;
        }
        // Draw rectangles
        else if (i == rectanglesAt[s]) {
            iSetColor(rectangleArr[s].r, rectangleArr[s].g, rectangleArr[s].b);
            iRectangle(rectangleArr[s].x, rectangleArr[s].y, rectangleArr[s].dx, rectangleArr[s].dy);
            s++;
        }
        // Draw filled rectangles
        else if (i == filledRectsAt[t]) {
            iSetColor(filledRectArr[t].r, filledRectArr[t].g, filledRectArr[t].b);
            iFilledRectangle(filledRectArr[t].x, filledRectArr[t].y, filledRectArr[t].dx, filledRectArr[t].dy);
            t++;
        }
        // Draw ellipses
        else if (i == ellipsesAt[u]) {
            iSetColor(ellipseArr[u].r, ellipseArr[u].g, ellipseArr[u].b);
            iEllipse(ellipseArr[u].x, ellipseArr[u].y, ellipseArr[u].da, ellipseArr[u].db, 1000);
            u++;
        }
        // Draw filled ellipses
        else if (i == filledEllipsesAt[v]) {
            iSetColor(filledEllipseArr[v].r, filledEllipseArr[v].g, filledEllipseArr[v].b);
            iFilledEllipse(filledEllipseArr[v].x, filledEllipseArr[v].y, filledEllipseArr[v].da, filledEllipseArr[v].db, 1000);
            v++;
        }
        // Draw lines
        else if (i == linesAt[w]) {
            iSetColor(lineArr[w].r, lineArr[w].g, lineArr[w].b);
            iLine(lineArr[w].x1, lineArr[w].y1, lineArr[w].x2, lineArr[w].y2);
            w++;
        }
        // Draw polygons
        else if (i == polysAt[e]) {
            iSetColor(polyArr[e].r, polyArr[e].g, polyArr[e].b);
            iPolygon(polyArr[e].x, polyArr[e].y, polyArr[e].n);
            e++;
        }
        // Draw filled polygons
        else if (i == filledPolysAt[f]) {
            iSetColor(filledPolyArr[f].r, filledPolyArr[f].g, filledPolyArr[f].b);
            iFilledPolygon(filledPolyArr[f].x, filledPolyArr[f].y, filledPolyArr[f].n);
            f++;
        }
        // Draw points if not matched with any shapes
        else {
            iSetColor(PointsArr[i].r, PointsArr[i].g, PointsArr[i].b);
            iFilledCircle(PointsArr[i].x, PointsArr[i].y, PointsArr[i].size);
        }
    }
}

void iDraw() {  
    iClear();
    iSetColor(211, 211, 211);  
    iFilledRectangle(0, 0, 660, 790);  
    
    if (mode == 0) {                  
        double x[] = {330.0, 680.0, 210.0, 100.0}; 
        double y[] = { 680.0, 680.0, 210.0, 100.0  };  
        int numPoints = 4; 
        iFilledPolygon(x, y, numPoints); // Draw a polygon using the provided coordinates
        
        iSetColor(255, 192, 203);
        iFilledRectangle(330.0, 680.0, 200.0, 90.0); // Draw a rectangle
        
        iFilledCircle(330.0, 495.0, 105.0); // Draw a circle
        
        iFilledEllipse(330.0, 325.0, 105.0, 45.0); // Draw an ellipse
        iFilledEllipse(330.0, 155.0, 105.0, 45.0); // Draw another ellipse

        iShowBMP(210, 640, "logoo.bmp");

        iSetColor(255, 192, 203);
        iText(240, 488, "Create a New Drawing", GLUT_BITMAP_HELVETICA_18);
        iText(242, 318, "Edit a Saved Drawing", GLUT_BITMAP_HELVETICA_18);
        iText(237, 148, "View a Saved Drawing", GLUT_BITMAP_HELVETICA_18);
    }

    if (mode == 1)  {                  
        displayThings();
        iShowBMP(425, 690, "icons.bmp");

        iSetColor(0,0,0);

        if (!showingMoreIcons)    
            iShowBMP(617, 680, "more.bmp");
        else    
        {
            iShowBMP(454, 678, "line.bmp");
            iShowBMP(480, 633, "moreShapes.bmp");
            iShowBMP(617, 680, "closemore.bmp");
            iShowBMP(486, 678, "shapetools.bmp");
            iShowBMP(620, 5, "return.bmp");
        }

        iSetColor(curr_r, curr_g, curr_b);              
        iFilledRectangle(14, 740, 16, 16);

        if(showPallete) 
            iShowBMP(180, 665, "colors.bmp");

        if (showPrompt) {
            if(threeSecCnt>4)
                threeSecCnt=0;

            iResumeTimer(0);

            iSetColor(0,0,0);
            iText(15, 770, promptMsg[promptMsgNo], GLUT_BITMAP_HELVETICA_12);
        }

        if (showSavePrompt) {
            iSetColor(250, 0, 137);
            iFilledRectangle (330, 415, 250, 130);
            iSetColor(255, 148, 180);
            iFilledRectangle(330, 415, 240, 120);

            iShowBMP(230, 440, "Save.bmp");
            iSetColor(255, 255, 255);
            iFilledRectangle(210, 390, 250, 25);

            iShowBMP(275,320, "savebtn.bmp");
            iSetColor(0,0,0);
            iText(214, 397, save_filename, GLUT_BITMAP_HELVETICA_12);
        }
    }

    if (mode == 2 || mode == 3) {                  
        iShowBMP(150, 600, "Load.bmp");

        for (int i=0; i<save_cnt; i++) {
            iSetColor(255,123,192);
            iFilledRectangle(80, 550-40*i, 200, 30);

            iSetColor(255, 255, 255);
            iText(90, 560-40*i, save_names[i], GLUT_BITMAP_HELVETICA_18);
        }
    }

    if (mode == 4) {
        displayThings();

        if (showPrompt) {
            if(threeSecCnt>4)
                threeSecCnt=0;

            iResumeTimer(0);

            iSetColor(0,0,0);
            iText(15, 770, promptMsg[promptMsgNo], GLUT_BITMAP_HELVETICA_12);
        }
    }
}

           void iMouseMove(int mx, int my) {

    if (mode==1) {              //drawing screen

         if(tool==0) {               //free draw tool
           PointsArr[total_pts].x= mx;
           PointsArr[total_pts].y= my;
           PointsArr[total_pts].r= curr_r;
           PointsArr[total_pts].g= curr_g;
           PointsArr[total_pts].b= curr_b;
           PointsArr[total_pts].size= curr_pts_size;

           total_pts++;
           cout << mx << " " << my<< " " << total_pts<< endl;
        }

        if(tool==2) {           // free erase tool

           PointsArr[total_pts].x= mx;
           PointsArr[total_pts].y= my;
           PointsArr[total_pts].r= 255;
           PointsArr[total_pts].g= 255;
           PointsArr[total_pts].b= 255;
           PointsArr[total_pts].size= curr_pts_size;

           total_pts++;

        }

    }

}
       

void iMouse(int button, int state, int mx, int my) {

    if (mode==0) {                  //homescreen

        if (mx>=330-105 && mx<=330+105 && my>=495-45 && my<=495+45 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
            {mode=1, showPrompt=1; return; }
                                            //enter drawing mode

         if (mx>=330-105 && mx<=330+105 && my>=325-45 && my<=325+45 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
                {
                readList();

                mode =2;                // load paintings page
                }

         if (mx>=330-105 && mx<=330+105 && my>=155-45 && my<=155+45 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
         {
                readList();

                mode =3;                // load painting to view page
         }

    }

    if (mode==1) {           // drawing screen


        if (showingMoreIcons && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {         // selecting from shape tools

            if (tool!=6 && mx>=490 && mx<=516 && my>=684 && my<=704) {tool=6, showPrompt=1, promptMsgNo=13; return;}
                                                                                                            // set active tool to circle tool if not already

            if (tool!=7 && mx>=522 && mx<=561 && my>=686 && my<=704) {tool=7, showPrompt=1, promptMsgNo=14; return;}
                                                                                                            // set active tool to rectangle tool if not already

            if (tool!=8 && mx>=570 && mx<=607 && my>=686 && my<=704) {tool=8, showPrompt=1, promptMsgNo=15; return;}
                                                                                                            // set active tool to filled rectangle tool if not already


            //      489 647 525 670, 530 648 567 670, 575 646 607 672, 615 646 649 673

            if (tool!=9 && mx>=489 && mx<=525 && my>=647 && my<=670) {tool=9, showPrompt=1, promptMsgNo=16; return;}
                                                                                                            // set active tool to ellipse if not already

            if (tool!=10 && mx>=530 && mx<=567 && my>=647 && my<=670) {tool=10, showPrompt=1, promptMsgNo=17; return;}
                                                                                                            // set active tool to filled ellipse if not already

            if (tool!=13 && mx>=456 && mx<=484 && my>=681 && my<=708) {tool=13, showPrompt=1, promptMsgNo=18; return;}
                                                                                                            // set active tool to line tool if not already

            if (tool!=11 && mx>=575 && mx<=607 && my>=646 && my<=672) {tool=11, showPrompt=1, promptMsgNo=20; return;}
                                                                                                            // set active tool to polygon tool if not already

            if (tool!=12 && mx>=615 && mx<=649 && my>=646 && my<=672) {tool=12, showPrompt=1, promptMsgNo=22; return;}
                                                                                                            // set active tool to filled polygon tool if not already

            if (mx>= 620 && mx <= 652 && my>=5 && my<=37 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {

            mode=0; init(); freeMem(); erase();
            }

        }


        // toggle show more icons
        if (mx>=617 && mx<=617+32 && my>=680 && my<=680+32 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {

            if (showingMoreIcons) showingMoreIcons=0;
            else showingMoreIcons =1;
            return;

        }

        if(tool==5 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && mx>=289 && mx<=385 && my>=331 && my<=355)
           {
            len=0, tool=1, showSavePrompt=0, SaveFile(save_filename);   return;}                                      // when final save button is clicked


        if(tool!=0 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)

            if (mx>=455 && mx<=483 && my>=761 && my<=782) {
                    tool=0; showPrompt=1; promptMsgNo=0;    return;     // set active tool to free draw, if active not free draw
            }

        if(tool!=1 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)

            if (mx>=491 && mx<=526 && my>=763 && my<=782) {      // set active tool to precise draw and erase, if not already
                    tool=1; showPrompt=1; promptMsgNo=1;    return;
            }

        if(tool!=2 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)

            if (mx>=532 && mx<=563 && my>=766 && my<=783) {     // set active tool to free eraser, if not already
                     tool=2; showPrompt=1; promptMsgNo=2;   return;
            }

         if(curr_pts_size!=1 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)

            if (mx>=457 && mx<=478 && my>=729 && my<=741) {     // set small brush size, if not already
                     curr_pts_size=1; showPrompt=1; promptMsgNo=3;  return;
            }

        if(tool!=3 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)

            if (mx>=573 && mx<=602 && my>=759 && my<=787) {
                  tool=3; showPrompt=1; promptMsgNo=7;  return;   // set active tool to textBox, if active not textBox
        }

         if(curr_pts_size!=5 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)

            if (mx>=491 && mx<=514 && my>=725 && my<=742) {     // set medium brush size, if not already
                     curr_pts_size=5; showPrompt=1; promptMsgNo=4; return;
            }

         if(curr_pts_size!=18 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)

            if (mx>=529 && mx<=566 && my>=716 && my<=752) {     // set large brush size, if not already
                     curr_pts_size=18; showPrompt=1; promptMsgNo=5; return;
            }

         if(curr_pts_size!=30 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)

            if (mx>=574 && mx<=610 && my>=718 && my<=752) {     // set XL brush size, if not already
                     curr_pts_size=30; showPrompt=1; promptMsgNo=6; return;
            }

         if (mx>=616 && mx<=646 && my>=758 && my<=787 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN )
                                                                    // save btn
            {tool=5, showSavePrompt=1; return;}


         if (mx>=617 && mx<=648 && my>=719 && my<=751 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) // toggle color pallete
         {
             if (showPallete) showPallete=0;
             else showPallete =1;
             return;
         }





        if(tool==1) {               // precise draw point tool

             if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {              // in precise mode left click to draw a point

            PointsArr[total_pts].x= mx;
            PointsArr[total_pts].y= my;
            PointsArr[total_pts].r= curr_r;
            PointsArr[total_pts].g= curr_g;
            PointsArr[total_pts].b= curr_b;
            PointsArr[total_pts].size= curr_pts_size;

            total_pts++;

            }

            if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {              // in precise mode, right click to erase a point

           PointsArr[total_pts].x= mx;
           PointsArr[total_pts].y= my;
           PointsArr[total_pts].r= 255;
           PointsArr[total_pts].g= 255;
           PointsArr[total_pts].b= 255;
           PointsArr[total_pts].size= curr_pts_size;

           total_pts++;
            }
        }

        if (tool==3) {              // text Box tool

        textsAt[textsAtCnt]=total_pts++;                      // total_pts is actually total items/things
        textBoxArr[textsAtCnt].r=curr_r;                        // at this total_pts, there is a textbox, store this total_pts in arr, and increment it
        textBoxArr[textsAtCnt].g=curr_g;
        textBoxArr[textsAtCnt].b=curr_b;
        textBoxArr[textsAtCnt].x=mx;
        textBoxArr[textsAtCnt].y=my;

        tool=4; showPrompt=1; promptMsgNo=8;

        }

        if (tool==6 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {      // circle tool

            circlesAt[circleCnt]= total_pts++;                              // total_pts is actually total items/things
            circleArr[circleCnt].x= mx;                                        // at this total_pts, there is a circle, store this total_pts in arr, and increment it
            circleArr[circleCnt].y= my;
            circleArr[circleCnt].r= curr_r;
            circleArr[circleCnt].g= curr_g;
            circleArr[circleCnt].b= curr_b;
            circleArr[circleCnt].size= curr_pts_size+28;

            circleCnt++;

        }

        if (tool==6 && button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {         // filled circle tool

            filledCirclesAt[filledCircleCnt]= total_pts++;              // total_pts is actually total items/things
            filledCircleArr[filledCircleCnt].x=mx;                          // at this total_pts, there is a filled circle, store this total_pts in arr, and increment it
            filledCircleArr[filledCircleCnt].y= my;
            filledCircleArr[filledCircleCnt].r= curr_r;
            filledCircleArr[filledCircleCnt].g= curr_g;
            filledCircleArr[filledCircleCnt].b= curr_b;
            filledCircleArr[filledCircleCnt].size= curr_pts_size+28;

            filledCircleCnt++;
        }

        if (tool==7)  {         // rectangle tool

            rectanglesAt[rectangleCnt]= total_pts++;
            rectangleArr[rectangleCnt].x=mx;
            rectangleArr[rectangleCnt].y=my;
            rectangleArr[rectangleCnt].r=curr_r;
            rectangleArr[rectangleCnt].g=curr_g;
            rectangleArr[rectangleCnt].b=curr_b;

            if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {            // wide

                rectangleArr[rectangleCnt].dx=3*curr_pts_size+50;
                rectangleArr[rectangleCnt].dy= 10*(3*curr_pts_size+50)/17;

            }

            if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {        // tall

                rectangleArr[rectangleCnt].dy=3*curr_pts_size+50;
                rectangleArr[rectangleCnt].dx= 10*(3*curr_pts_size+50)/17;
            }

            rectangleCnt++;
        }

        if (tool==8)  {         // filled rectangle tool

            filledRectsAt[filledRectCnt]= total_pts++;
            filledRectArr[filledRectCnt].x=mx;
            filledRectArr[filledRectCnt].y=my;
            filledRectArr[filledRectCnt].r=curr_r;
            filledRectArr[filledRectCnt].g=curr_g;
            filledRectArr[filledRectCnt].b=curr_b;

            if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {            // wide

                filledRectArr[filledRectCnt].dx=3*curr_pts_size+50;
                filledRectArr[filledRectCnt].dy= 10*(3*curr_pts_size+50)/17;

            }

            if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {        // tall

                filledRectArr[filledRectCnt].dy=3*curr_pts_size+50;
                filledRectArr[filledRectCnt].dx= 10*(3*curr_pts_size+50)/17;
            }

            filledRectCnt++;
        }

        if (tool==9) {              // ellipse tool

            ellipsesAt[ellipseCnt]=total_pts++;
            ellipseArr[ellipseCnt].x=mx;
            ellipseArr[ellipseCnt].y=my;
            ellipseArr[ellipseCnt].r=curr_r;
            ellipseArr[ellipseCnt].g=curr_g;
            ellipseArr[ellipseCnt].b=curr_b;

            if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {            // wide

                ellipseArr[ellipseCnt].da=(3*curr_pts_size+50)/2;
                ellipseArr[ellipseCnt].db= 5*(3*curr_pts_size+50)/17;

            }

            if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {            // tall

                ellipseArr[ellipseCnt].db=(3*curr_pts_size+50)/2;
                ellipseArr[ellipseCnt].da= 5*(3*curr_pts_size+50)/17;

            }

            ellipseCnt++;

        }

        if (tool==10) {              // filled ellipse tool

            filledEllipsesAt[filledEllipseCnt]=total_pts++;
            filledEllipseArr[filledEllipseCnt].x=mx;
            filledEllipseArr[filledEllipseCnt].y=my;
            filledEllipseArr[filledEllipseCnt].r=curr_r;
            filledEllipseArr[filledEllipseCnt].g=curr_g;
            filledEllipseArr[filledEllipseCnt].b=curr_b;

            if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {            // wide

                filledEllipseArr[filledEllipseCnt].da=(3*curr_pts_size+50)/2;
                filledEllipseArr[filledEllipseCnt].db= 5*(3*curr_pts_size+50)/17;

            }

            if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {            // tall

                filledEllipseArr[filledEllipseCnt].db=(3*curr_pts_size+50)/2;
                filledEllipseArr[filledEllipseCnt].da= 5*(3*curr_pts_size+50)/17;

            }

            filledEllipseCnt++;

        }

        if (tool==13 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {             // line tool


            lineArr[lineCnt].r=curr_r;
            lineArr[lineCnt].g=curr_g;
            lineArr[lineCnt].b=curr_b;
            lineArr[lineCnt].x1= mx;
            lineArr[lineCnt].y1= my;

            tool=14, showPrompt=1, promptMsgNo=19;

        }

        if (tool==14 && button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {         // end line tool

            lineArr[lineCnt].x2= mx;
            lineArr[lineCnt].y2= my;
            linesAt[lineCnt]=total_pts++;

            tool=13, showPrompt=1, promptMsgNo=18, lineCnt++;


        }

        if (tool==11 && button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {             // polygon tool

          if (polyArr[polyCnt].n==0) {              // for the first selected point
            polysAt[polyCnt]=total_pts++;
            polyArr[polyCnt].r=curr_r;
            polyArr[polyCnt].g=curr_g;
            polyArr[polyCnt].b=curr_b;
            }

            polyArr[polyCnt].x[polyArr[polyCnt].n]=mx;
            polyArr[polyCnt].y[polyArr[polyCnt].n]=my;

            polyArr[polyCnt].n++;
            showPrompt=1, promptMsgNo=21;

        }

         if (tool==11 && polyArr[polyCnt].n!=0  && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) { // polygon end

            polyArr[polyCnt].x[polyArr[polyCnt].n]=mx;
            polyArr[polyCnt].y[polyArr[polyCnt].n]=my;

            polyArr[polyCnt].n++;

            polyCnt++;

            showPrompt=1, promptMsgNo=20;

         }

         if (tool==12 && button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {             // filled polygon tool

          if (filledPolyArr[filledPolyCnt].n==0) {              // for the first selected point
            filledPolysAt[filledPolyCnt]=total_pts++;
            filledPolyArr[filledPolyCnt].r=curr_r;
            filledPolyArr[filledPolyCnt].g=curr_g;
            filledPolyArr[filledPolyCnt].b=curr_b;
            }

            filledPolyArr[filledPolyCnt].x[filledPolyArr[filledPolyCnt].n]=mx;
            filledPolyArr[filledPolyCnt].y[filledPolyArr[filledPolyCnt].n]=my;

            filledPolyArr[filledPolyCnt].n++;
            showPrompt=1, promptMsgNo=21;

        }

         if (tool==12 && filledPolyArr[filledPolyCnt].n!=0  && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {      // filled polygon end

            filledPolyArr[filledPolyCnt].x[filledPolyArr[filledPolyCnt].n]=mx;
            filledPolyArr[filledPolyCnt].y[filledPolyArr[filledPolyCnt].n]=my;

            filledPolyArr[filledPolyCnt].n++;

            filledPolyCnt++;

            showPrompt=1, promptMsgNo=22;

         }

     if(tool!=1 && tool!=6 && tool!=7 && tool!=8 && tool!=9 && tool!=10 && tool!=11 && tool!=12 && tool!=13 && tool!=14 && button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
                                    curr_r=0, curr_g=0, curr_b=0;          // right click to set color to black


    if (showPallete && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {                 // selecting colors in pallete

            if (mx>=180 && mx<=213) {

               if (my>=775 && my<=793) curr_r=169, curr_g=212, curr_b=255;
               if (my>=753 && my<=771) curr_r=148, curr_g=196, curr_b=244;
               if (my>=731 && my<=749) curr_r=120, curr_g=180, curr_b=236;
               if (my>=709 && my<=727) curr_r=86, curr_g=156, curr_b=216;
               if (my>=687 && my<=705) curr_r=46, curr_g=123, curr_b=201;
               if (my>=665 && my<=683) curr_r=6, curr_g=94, curr_b=183;

            }

            if (mx>=217 && mx<=250) {

               if (my>=775 && my<=793) curr_r=251, curr_g=194, curr_b=183;
               if (my>=753 && my<=771) curr_r=243, curr_g=156, curr_b=146;
               if (my>=731 && my<=749) curr_r=230, curr_g=118, curr_b=107;
               if (my>=709 && my<=727) curr_r=211, curr_g=83, curr_b=72;
               if (my>=687 && my<=705) curr_r=206, curr_g=52, curr_b=44;
               if (my>=665 && my<=683) curr_r=187, curr_g=32, curr_b=27;

            }

            if (mx>=254 && mx<=287) {

               if (my>=775 && my<=793) curr_r=255, curr_g=219, curr_b=157;
               if (my>=753 && my<=771) curr_r=253, curr_g=211, curr_b=127;
               if (my>=731 && my<=749) curr_r=252, curr_g=200, curr_b=101;
               if (my>=709 && my<=727) curr_r=243, curr_g=185, curr_b=60;
               if (my>=687 && my<=705) curr_r=243, curr_g=175, curr_b=48;
               if (my>=665 && my<=683) curr_r=255, curr_g=169, curr_b=32;

            }

            if (mx>=291 && mx<=324) {

               if (my>=775 && my<=793) curr_r=119, curr_g=251, curr_b=150;
               if (my>=753 && my<=771) curr_r=98, curr_g=219, curr_b=126;
               if (my>=731 && my<=749) curr_r=81, curr_g=185, curr_b=106;
               if (my>=709 && my<=727) curr_r=61, curr_g=152, curr_b=85;
               if (my>=687 && my<=705) curr_r=40, curr_g=118, curr_b=66;
               if (my>=665 && my<=683) curr_r=19, curr_g=86, curr_b=43;

            }

            if (mx>=328 && mx<=361) {

               if (my>=775 && my<=793) curr_r=252, curr_g=184, curr_b=245;
               if (my>=753 && my<=771) curr_r=226, curr_g=130, curr_b=217;
               if (my>=731 && my<=749) curr_r=160, curr_g=79, curr_b=146;
               if (my>=709 && my<=727) curr_r=128, curr_g=50, curr_b=112;
               if (my>=687 && my<=705) curr_r=107, curr_g=27, curr_b=96;
               if (my>=665 && my<=683) curr_r=66, curr_g=17, curr_b=73;

            }

            if (mx>=365 && mx<=398) {

               if (my>=775 && my<=793) curr_r=251, curr_g=170, curr_b=189;
               if (my>=753 && my<=771) curr_r=238, curr_g=144, curr_b=162;
               if (my>=731 && my<=749) curr_r=203, curr_g=112, curr_b=127;
               if (my>=709 && my<=727) curr_r=174, curr_g=81, curr_b=98;
               if (my>=687 && my<=705) curr_r=131, curr_g=40, curr_b=53;
               if (my>=665 && my<=683) curr_r=90, curr_g=13, curr_b=23;

            }

            if (mx>=402 && mx<=435) {

               if (my>=775 && my<=793) curr_r=253, curr_g=208, curr_b=219;
               if (my>=753 && my<=771) curr_r=217, curr_g=166, curr_b=175;
               if (my>=731 && my<=749) curr_r=172, curr_g=111, curr_b=116;
               if (my>=709 && my<=727) curr_r=137, curr_g=72, curr_b=78;
               if (my>=687 && my<=705) curr_r=108, curr_g=49, curr_b=51;
               if (my>=665 && my<=683) curr_r=85, curr_g=20, curr_b=28;

            }
    return;
         }


    }

    if (mode==2 || mode==3) {              // load screen

        if ( mx>= 80 && mx <= 280 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {

            int ind= (580-my)/40;
            if (ind < save_cnt) {
                LoadFile(save_names[ind]);
               if (mode==2) mode =1;
               if (mode==3) mode =4;
                }
             }
    }

    if (mode==4 && mx>= 620 && mx <= 652 && my>=5 && my<=37 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {

        mode=0; init(); freeMem(); erase();

    }
}






    void iKeyboard(unsigned char key) {
    if (mode == 1 && tool != 4 && tool != 5 && key == 'w') {
        curr_r = 255, curr_g = 255, curr_b = 255; // press w to set color to white
    }
    if (mode == 1 && tool != 4 && tool != 5 && key == 'b') {
        curr_r = 0, curr_g = 0, curr_b = 0; // press b to set color to black
    }
    if (tool == 4 && mode == 1) { // taking input for textbox
        if (key == '\r') {
            textBoxArr[textsAtCnt++].text[len] = '\0', tool = 3, len = 0, showPrompt = 1, promptMsgNo = 7;
        } else {
            if (key == 8 && len >= 0) {
                textBoxArr[textsAtCnt].text[len--] = '\0';
            } else {
                textBoxArr[textsAtCnt].text[len++] = key;
            }
        }
    }
    if (tool == 5 && mode == 1) { // taking input for savefile name
        if (key == '\r')  
            len = 0, tool = 1, showSavePrompt = 0, SaveFile(save_filename);
        else {
            if (key == 8 && len >= 0)  
                save_filename[len--] = '\0';
            else 
                save_filename[len++] = key;
        }
    }
}
    
    
    void iSpecialKeyboard(unsigned char key) {
}






int main() {

    mode=0;

    init();

    iSetTimer(1000, threeSec);
    threeSecCnt--;
    iPauseTimer(0);
	//void iInitialize(int width = 800, int height = 500, const char *title = "Paint Application");
    iInitialize(500,500,"Paint Application");

    freeMem();

	return 0;
}

void init() {

    total_pts=0;
    textsAtCnt=0; len=0, save_cnt=0, circleCnt=0, filledCircleCnt=0, rectangleCnt=0, filledRectCnt=0,
    ellipseCnt=0, filledEllipseCnt=0, lineCnt=0, polyCnt=0, filledPolyCnt=0;
    curr_r=0, curr_g=0, curr_b=0, curr_pts_size=1;
    tool=0, showingMoreIcons=0;
    showPrompt=0, showPallete=0, showSavePrompt=0;
    promptMsgNo=0;
    threeSecCnt=0;

}
     void freeMem() {

    free(PointsArr);
    free(textBoxArr);
    free(textsAt);
    free(circleArr);
    free(circlesAt);
    free(filledCircleArr);
    free(filledCirclesAt);
    free(rectanglesAt);
    free(rectangleArr);
    free(filledRectsAt);
    free(filledRectArr);
    free(ellipsesAt);
    free(ellipseArr);
    free(filledEllipsesAt);
    free(filledEllipseArr);
    free(linesAt);
    free(lineArr);
    free(polysAt);
    free(polyArr);
    free(filledPolysAt);
    free(filledPolyArr);

}


void erase() {
    PointsArr = (pts *) malloc(9999999 * sizeof(pts));
    textBoxArr = (textBox *) malloc(20 * sizeof(textBox));
    textsAt = (int *) malloc(20 * sizeof(int));
    circleArr = (circle *) malloc(100 * sizeof(circle));
    circlesAt = (int *) malloc(100 * sizeof(int));
    filledCircleArr = (filledCircle *) malloc(100 * sizeof(filledCircle));
    filledCirclesAt = (int *) malloc(100 * sizeof(int));
    rectangleArr = (rectangle *) malloc(100 * sizeof(rectangle));
    rectanglesAt = (int *) malloc(100 * sizeof(int));
    filledRectArr = (filledRect *) malloc(100 * sizeof(filledRect));
    filledRectsAt = (int *) malloc(100 * sizeof(int));
    ellipseArr = (ellipse *) malloc(100 * sizeof(ellipse));
    ellipsesAt = (int *) malloc(100 * sizeof(int));
    filledEllipseArr = (filledEllipse *) malloc(100 * sizeof(filledEllipse));
    filledEllipsesAt = (int *) malloc(100 * sizeof(int));
    lineArr = (line *) malloc(100 * sizeof(line));
    linesAt = (int *) malloc(100 * sizeof(int));
    polyArr = (poly *) malloc(50 * sizeof(poly));
    polysAt = (int *) malloc(50 * sizeof(int));
    filledPolyArr = (filledPoly *) malloc(50 * sizeof(filledPoly));
    filledPolysAt = (int *) malloc(50 * sizeof(int));
}

















