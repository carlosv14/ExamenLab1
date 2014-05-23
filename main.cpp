//The headers
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include <string>
#include "burbujita.h"
#include <list>
#include <stdlib.h>
#include "boton.h"
#include <sstream>
#include <string>
#include "badbubbles.h"
#include "SDL/SDL_mixer.h"
#include "congeladas.h"
#include "explosive.h"
#include <fstream>
#include "bonus.h"
using namespace std;

//Screen attributes
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;
int FRAMES_PER_SECOND = 100;
//The surfaces

stringstream stream;
SDL_Surface *background = NULL;
SDL_Surface * puntos = NULL;
SDL_Surface *screen = NULL;
SDL_Surface *score = NULL;
SDL_Surface *seconds = NULL;
SDL_Surface *besc =NULL;
SDL_Surface *besc1 =NULL;
SDL_Surface *besc2 =NULL;
SDL_Surface *besc3 =NULL;
SDL_Surface *gan =NULL;
SDL_Surface *menus = NULL;
SDL_Surface *per = NULL;
SDL_Surface *instru = NULL;
SDL_Surface *bc = NULL;
Mix_Music *music = NULL;
Mix_Chunk *tap = NULL;
Mix_Chunk *badb = NULL;
Mix_Chunk *start = NULL;
Mix_Chunk *loose = NULL;
Mix_Chunk *ice = NULL;
Mix_Chunk *win = NULL;
Mix_Chunk *exp = NULL;

//The event structure

list<int> puntaje;
SDL_Event event;

//The font
TTF_Font *font = NULL;

//The color of the font
SDL_Color textColor = { 0, 0, 0 };

class Timer
{
private:
    //The clock time when the timer started
    int startTicks;

    //The ticks stored when the timer was paused
    int pausedTicks;

    //The timer status
    bool paused;
    bool started;

public:
    //Initializes variables
    Timer();

    //The various clock actions
    void start();
    void stop();
    void pause();
    void unpause();

    //Gets the timer's time
    int get_ticks();

    //Checks the status of the timer
    bool is_started();
    bool is_paused();
};
Timer::Timer()
{
    //Initialize the variables
    startTicks = 0;
    pausedTicks = 0;
    paused = false;
    started = false;
}

void Timer::start()
{
    //Start the timer
    started = true;

    //Unpause the timer
    paused = false;

    //Get the current clock time
    startTicks = SDL_GetTicks();
}

void Timer::stop()
{
    //Stop the timer
    started = false;

    //Unpause the timer
    paused = false;
}

void Timer::pause()
{
    //If the timer is running and isn't already paused
    if( ( started == true ) && ( paused == false ) )
    {
        //Pause the timer
        paused = true;

        //Calculate the paused ticks
        pausedTicks = SDL_GetTicks() - startTicks;
    }
}

void Timer::unpause()
{
    //If the timer is paused
    if( paused == true )
    {
        //Unpause the timer
        paused = false;

        //Reset the starting ticks
        startTicks = SDL_GetTicks() - pausedTicks;

        //Reset the paused ticks
        pausedTicks = 0;
    }
}

int Timer::get_ticks()
{
    //If the timer is running
    if( started == true )
    {
        //If the timer is paused
        if( paused == true )
        {
            //Return the number of ticks when the timer was paused
            return pausedTicks;
        }
        else
        {
            //Return the current time minus the start time
            return SDL_GetTicks() - startTicks;
        }
    }

    //If the timer isn't running
    return 0;
}

bool Timer::is_started()
{
    return started;
}

bool Timer::is_paused()
{
    return paused;
}
SDL_Surface *load_image( std::string filename )
{

    //Return the optimized surface
    return IMG_Load( filename.c_str() );

}

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL )
{
    //Holds offsets
    SDL_Rect offset;

    //Get offsets
    offset.x = x;
    offset.y = y;

    //Blit
    SDL_BlitSurface( source, clip, destination, &offset );
}

bool init()
{
    //Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        return false;
    }

    //Set up the screen
    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );

    //If there was an error in setting up the screen
    if( screen == NULL )
    {
        return false;
    }

    //Initialize SDL_ttf
    if( TTF_Init() == -1 )
    {
        return false;
    }
    if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
    {
        return false;
    }
    //Set the window caption
    SDL_WM_SetCaption( "Press an Arrow Key", NULL );


    //If everything initialized fine
    return true;
}

bool load_files()
{
    //Load the background image
    background = load_image( "background.png" );
    //Open the font
    font = TTF_OpenFont( "lazy.ttf", 20 );
    gan =load_image("op.png");
    menus = load_image("op2.png");

    per = load_image("lost.png");

    instru = load_image("instr.png");

    bc = load_image("bc.png");
    //If there was a problem in loading the background
    if( background == NULL )
    {
        return false;
    }

    //If there was an error in loading the font
    if( font == NULL )
    {
        return false;
    }

    exp = Mix_LoadWAV( "explode.wav" );
    tap = Mix_LoadWAV( "Bubble.ogg" );
    badb = Mix_LoadWAV( "BubbleBad.ogg" );
    start= Mix_LoadWAV( "StartGame.ogg" );
    loose= Mix_LoadWAV( "LosingSound.ogg" );
    ice= Mix_LoadWAV( "icecrack.wav" );
    win= Mix_LoadWAV( "Winning.ogg" );
    music = Mix_LoadMUS( "clock.wav" );
    if(tap == NULL)
    {
        return false;
    }
    if(badb == NULL)
    {
        return false;
    }
    if(start== NULL)
    {
        return false;
    }
    if(loose == NULL)
    {
        return false;
    }
    if(ice == NULL)
    {
        return false;
    }
    if(win == NULL)
    {
        return false;
    }
    if(exp == NULL)
    {
        return false;
    }
    //If everything loaded fine
    return true;
}

void clean_up()
{
    //Free the surfaces

    //Close the font
    TTF_CloseFont( font );

    //Quit SDL_ttf
    TTF_Quit();

    Mix_CloseAudio();


    Mix_FreeChunk( tap );
    Mix_FreeChunk( badb );
    Mix_FreeChunk( start );
    Mix_FreeChunk( loose );
    Mix_FreeChunk( ice );
    Mix_FreeChunk( exp);
    Mix_FreeMusic( music );

    SDL_FreeSurface( background );


    SDL_FreeSurface(gan);

    SDL_FreeSurface(per);

    SDL_FreeSurface(instru);
     SDL_FreeSurface(bc);

    //Quit SDL
    SDL_Quit();
}

void ganador(int scor)
{
    bool sonar = true;
    bool quitgan = false;
    while(quitgan == false)
    {
        //While there's events to handle
        while( SDL_PollEvent( &event ) )
        {
            //If the user has Xed out the window
            if( event.type == SDL_QUIT )
            {
                //Quit the program
                quitgan = true;
            }
        }
        std::stringstream sc;

        //Convert the timer's time to a string
        sc<<(scor);

        //Render the time surface
        puntos = TTF_RenderText_Solid( font, sc.str().c_str(), textColor );

        //Apply the time surface
        if(sonar)
        {
            Mix_PlayChannel( -1, win, 0 );
            sonar = false;

        }
        apply_surface(0,0,gan,screen);
        apply_surface( ( SCREEN_WIDTH - puntos->w ) / 2,( SCREEN_WIDTH ) / 2 , puntos, screen );
        SDL_FreeSurface(puntos);

        if( SDL_Flip( screen ) == -1 )
        {
            return ;
        }
    }
}
void perdedor(int scor)
{
    bool sonar = true;
    bool quitper = false;
    while(quitper == false)
    {
        //While there's events to handle
        while( SDL_PollEvent( &event ) )
        {
            //If the user has Xed out the window
            if( event.type == SDL_QUIT )
            {
                //Quit the program
                quitper = true;
            }
        }
        std::stringstream sc;

        //Convert the timer's time to a string
        sc<<(scor);

        //Render the time surface
        puntos = TTF_RenderText_Solid( font, sc.str().c_str(), textColor );
        if(sonar)
        {
            Mix_PlayChannel( -1, loose, 0 );
            sonar = false;
        }
        apply_surface(0,0,per,screen);
        apply_surface( ( SCREEN_WIDTH - puntos->w ) / 2,( SCREEN_WIDTH ) / 2 , puntos, screen );
        SDL_FreeSurface(puntos);
        if( SDL_Flip( screen ) == -1 )
        {
            return ;
        }
    }

}


void guardar(int scor)
{
    puntaje.push_back(scor);
    puntaje.sort();
    puntaje.reverse();
    ofstream in("puntaje");
    list<int>::iterator i=puntaje.begin();
    for (i=puntaje.begin(); i!=puntaje.end(); ++i)
    {
        in<<*i<<endl;
    }

}

void rellenar()
{

    ifstream out("puntaje");
    int n;
    while(out>>n)
    {
        puntaje.push_back(n);
    }

}
void bestc()
{
    bool quitper = false;
    while(quitper == false)
    {
        //While there's events to handle
        while( SDL_PollEvent( &event ) )
        {
            //If the user has Xed out the window
            if( event.type == SDL_QUIT )
            {
                //Quit the program
                quitper = true;
            }
        }
        apply_surface(0,0,bc,screen);
        list<int>::iterator i=puntaje.begin();
        std::stringstream cl;
        std::stringstream cl1;
        std::stringstream cl2;
        std::stringstream cl3;

        int n=0;
        int f;

        for (i=puntaje.begin(); i!=puntaje.end(); ++i)
        {
            if(n==0)
            {
                f=*i;
                cl<<(f);
                besc = TTF_RenderText_Solid( font, cl.str().c_str(), textColor );

            }
            if(n==1)
            {
                f=*i;
                cl1<<(f);
                besc1 = TTF_RenderText_Solid( font, cl1.str().c_str(), textColor );
            }

            if(n==2)
            {
                f=*i;
                cl2<<(f);
                besc2 = TTF_RenderText_Solid( font, cl2.str().c_str(), textColor );
            }

            if(n==3)
            {
                f=*i;
                cl3<<(f);
                besc3 = TTF_RenderText_Solid( font, cl3.str().c_str(), textColor );
            }
            n++;


        }
        apply_surface(80 ,310 ,besc, screen );
        apply_surface(240 ,380 ,besc1, screen );
        apply_surface(408 ,310 ,besc2, screen );
        apply_surface(550 ,380 ,besc3, screen );

    SDL_FreeSurface( besc);

    SDL_FreeSurface( besc1 );

    SDL_FreeSurface( besc2 );

    SDL_FreeSurface( besc3);
        if( SDL_Flip( screen ) == -1 )
        {
            return ;
        }
    }


}

void juego()
{
    Uint32 starter =0;
    bool mover = true;
    bool moving = true;
    bool quitjuego = false;
    int frame=0;
    Timer myTimer;
    srand(time(NULL));
    list <burbujita*> burbujas;
    Timer fps;
    int s=0;
    int tiempo = 0;
    int looser =0;
    int tiempoex = 0;
    myTimer.start();
    while( quitjuego == false )
    {

        fps.start();
        frame++;
        if(frame%100==0 && mover && moving)
        {
            burbujas.push_back(new burbujita(0,rand()%SCREEN_HEIGHT/2,screen,load_image("burbuja.png")));
        }
        else if(frame%250==0 && mover && moving)
        {
            burbujas.push_back(new congeladas(0,rand()%SCREEN_HEIGHT/2,screen,load_image("burbujaz.png")));
        }
        else if(frame%350 == 0 && mover && moving)
        {
            burbujas.push_back(new bonus(0,rand()%SCREEN_HEIGHT/2,screen,load_image("extra.png")));

        }
        else if(frame%450==0 && mover && moving)
        {
            burbujas.push_back(new badbubbles(0,rand()%SCREEN_HEIGHT/2,screen,load_image("bubblebad.png")));
        }
        else if(frame%550==0 && mover && moving)
        {
            burbujas.push_back(new explosive(0,rand()%SCREEN_HEIGHT/2,screen,load_image("red.png")));

        }

        int clickx =-1;
        int clicky= -1;
        //While there's events to handle
        while( SDL_PollEvent( &event ) )
        {
            //If the user has Xed out the window
            if( event.type == SDL_QUIT )
            {
                //Quit the program
                Mix_PauseMusic();
                quitjuego = true;
            }


            if(event.type == SDL_MOUSEBUTTONDOWN)
            {

                if(event.button.button == SDL_BUTTON_LEFT)
                {
                    clickx = event.button.x;
                    clicky = event.button.y;

                }
            }
            if( Mix_PlayingMusic() == 0 )
            {
                //Play the music
                if( Mix_PlayMusic( music, -1 ) == -1 )
                {
                    return;
                }
            }
            else
            {
                //If the music is paused
                if( Mix_PausedMusic() == 1 )
                {
                    //Resume the music
                    Mix_ResumeMusic();
                }

            }  //Pause the music



        }

        //Update the screen
        apply_surface( 0, 0, background, screen );
        list<burbujita*>::iterator i=burbujas.begin();
        while(i!=burbujas.end())
        {
            if((*i)->borrar&&(*i)->tipo =="n")
            {
                s++;
                burbujita*temp = (*i);
                i = burbujas.erase(i);
                delete temp;
                if( Mix_PlayChannel( -1, tap, 0 ) == -1 )
                {
                    return;
                }
            }
            else if((*i)->borrar && (*i)->tipo =="c")
            {
                burbujita*temp = (*i);
                i = burbujas.erase(i);
                delete temp;
                mover = false;
                myTimer.pause();
                tiempo =0;

                if( Mix_PlayChannel( -1, ice, 0 ) == -1 )
                {
                    return;
                }
            }
            else if((*i)->borrar && (*i)->tipo =="b")
            {
                s--;
                looser++;
                burbujita*temp = (*i);
                i = burbujas.erase(i);
                delete temp;
                if( Mix_PlayChannel( -1, badb, 0 ) == -1 )
                {
                    return;
                }

            }
            else if((*i)->borrar && (*i)->tipo =="e")
            {
                if( Mix_PlayChannel( -1, exp, 0 ) == -1 )
                {
                    return;
                }
                burbujita*temp = (*i);
                i = burbujas.erase(i);
                delete temp;
                moving = false;
                tiempoex =0;

            }
            else if((*i)->borrar && (*i)->tipo =="bon")
            {
                burbujita*temp = (*i);
                i = burbujas.erase(i);
                delete temp;
                myTimer.stop();
                myTimer.start();

            }

            else if(!mover)
            {
                (*i)->dibujar();
                (*i)->logica(clickx,clicky);
            }
            else if(!moving )
            {

                (*i)->dibujar();
                (*i)->logica(clickx,clicky);
                if((*i)->tipo =="n")
                {
                    s++;
                }
                else if((*i)->tipo =="b")
                {
                    s--;
                    looser++;
                }else if((*i)->tipo =="bon"){
                    myTimer.stop();
                    myTimer.start();

                }

                burbujita*temp = (*i);
                i = burbujas.erase(i);
                delete temp;



            }
            else
            {
                (*i)->dibujar();
                (*i)->logica(clickx,clicky);
                (*i)->mover();
                if((*i)->x >= 640){
                burbujita*temp = (*i);
                i = burbujas.erase(i);
                delete temp;


                }


            }

            i++;





        }


        if(!mover && tiempo == 500)
        {
            mover =true;
            myTimer.unpause();
        }
        if(!moving && tiempoex ==50)
        {
            moving = true;
        }
        if(looser == 3 )
        {
            Mix_PauseMusic();
            perdedor(s);
            looser =0;
            quitjuego = true;

        }
        if(((myTimer.get_ticks()-starter)/1000)==30 && looser<3 )
        {
            Mix_PauseMusic();
            ganador(s);
            guardar(s);
            quitjuego = true;

        }
        std::stringstream puntaje;
        puntaje<<"score : "<<s;
        score= TTF_RenderText_Solid( font,puntaje.str().c_str(), textColor );
        apply_surface(  0, 0, score, screen );
        tiempo ++;
        tiempoex++;
        std::stringstream time;

        //Convert the timer's time to a string
        time << "Timer: " <<30- ((myTimer.get_ticks()-starter)/1000);

        //Render the time surface
        seconds = TTF_RenderText_Solid( font, time.str().c_str(), textColor );

        //Apply the time surface
        apply_surface( ( SCREEN_WIDTH - seconds->w ) / 2, 0, seconds, screen );

        SDL_FreeSurface(seconds);
        if( fps.get_ticks() < 1000 / FRAMES_PER_SECOND )
        {
            //Sleep the remaining frame time
            SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
        }

        if( SDL_Flip( screen ) == -1 )
        {
            return ;
        }

    }
}



void menu()
{
    int frame =0;


    boton b(200,0,screen,load_image("button.png"));
    boton b1(320,0,screen,load_image("button1.png"));
    boton b2(80,0,screen,load_image("button2.png"));
    boton b3(430, 0 ,screen ,load_image("bests.png"));
    bool quit =false;

    while( quit == false )
    {
        int clickx =-1;
        int clicky= -1;

        while( SDL_PollEvent( &event ) )
        {
            //If the user has Xed out the window
            if( event.type == SDL_QUIT )
            {
                //Quit the program
                quit = true;
            }
            if(event.type == SDL_MOUSEBUTTONDOWN)
            {

                if(event.button.button == SDL_BUTTON_LEFT)
                {
                    clickx = event.button.x;
                    clicky = event.button.y;
                    if(clickx>=b.x && clickx<=b.x+b.surface->w
                            &&clicky >=b.y&& clicky <=b.y+b.surface->h)
                    {
                        Mix_PlayChannel( -1, start, 0 );
                        juego();

                    }
                    if(clickx>=b1.x && clickx<=b1.x+b1.surface->w
                            &&clicky >=b1.y&& clicky <=b1.y+b1.surface->h)
                    {
                        bool quit = false;
                        while(quit == false)
                        {
                            //While there's events to handle
                            while( SDL_PollEvent( &event ) )
                            {
                                //If the user has Xed out the window
                                if( event.type == SDL_QUIT )
                                {
                                    //Quit the program
                                    quit = true;
                                }
                                if(event.key.keysym.sym== SDLK_RETURN)
                                {
                                    juego();
                                    quit = true;
                                }
                            }
                            apply_surface( 0 ,0, instru, screen );
                            if( SDL_Flip( screen ) == -1 )
                            {
                                return ;
                            }
                        }



                    }



                    if(clickx>=b2.x && clickx<=b2.x+b2.surface->w
                            &&clicky >=b2.y&& clicky <=b2.y+b2.surface->h)
                    {

                        exit(0);


                    }

                    if(clickx>=b3.x && clickx<=b3.x+b3.surface->w
                            &&clicky >=b3.y&& clicky <=b3.y+b3.surface->h)
                    {

                        bestc();


                    }



                }
            }


        }

        apply_surface(0,0,menus,screen);

        if(b.y<350)
        {
            b.y+=4;
            b1.y+=3;
            b2.y+=3;
            b3.y+=4;

        }

        b.dibujar();
        b1.dibujar();
        b2.dibujar();
        b3.dibujar();


        if( SDL_Flip( screen ) == -1 )
        {
            return ;
        }

    }

}
int main( int argc, char* args[] )
{
    //Quit flag
    bool quit = false;
    //Initialize
    if( init() == false )
    {
        return 1;
    }

    //Load the files
    if( load_files() == false )
    {
        return 1;
    }

    //Render the text

    rellenar();
    menu();
    //Clean up
    clean_up();

    return 0;
}
