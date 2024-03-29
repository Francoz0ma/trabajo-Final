#include <SFML/Graphics.hpp>
#include <time.h>
#include <list>
using namespace sf;
#include "entidad.h"



int main()
{
    srand(time(0));

    RenderWindow app(VideoMode(anchoPantalla, altoPantalla), "Space Survival"/*, Style::Fullscreen*/);
    app.setFramerateLimit(60);

    Texture t1,t2,t3,t4,t5,t55,t6,t7,t11,t12,t8,t9,t10;
    t1.loadFromFile("images/xx.png");
    t11.loadFromFile("images/spaceship.png");
    t12.loadFromFile("images/spaceship.png");
    t2.loadFromFile("images/background.jpg");
    t3.loadFromFile("images/explosions/type_C.png");
    t4.loadFromFile("images/rock.png");
    t5.loadFromFile("images/fire_red.png");
    t55.loadFromFile("images/fire_blue.png");
    t6.loadFromFile("images/rock_small.png");
    t7.loadFromFile("images/explosions/type_B.png");
    t8.loadFromFile("images/explosions/type_A.png");
    t9.loadFromFile("images/circulo.png");
    t10.loadFromFile("images/laserpiola.png");

    t1.setSmooth(true);
    t2.setSmooth(true);

    Sprite background(t2);

    Animacion sExplosion(t3, 0,0,256,256, 48, 0.5);
    Animacion sRock(t4, 0,0,64,64, 16, 0.2);
    Animacion sRock_small(t6, 0,0,64,64, 16, 0.2);
    Animacion sBullet(t5, 0,0,32,64, 16, 0.8);

    Animacion sBullet5(t55, 0,0,32,64, 16, 0.8);
    Animacion sPlayer(t1, 0,0,100,58, 1, 0);
    Animacion sPlayer_go11(t11, 0,40,40,40, 1, 0);
    Animacion sPlayer_go12(t12, 80,40,40,40, 1, 0);
    Animacion sPlayer_go(t1, 0,0,100,58, 1, 0);
    Animacion sExplosion_ship(t7, 0,0,192,192, 64, 0.5);

    Animacion sDisparomejorado(t8, 0,0,50,50, 20, 0.1);
    Animacion scirculo(t9, 0,0,150,147,64, 0);

    Animacion slaserpiola(t10, 0,0,320,1080, 10, 0.7);

    std::list<Entidad*> entidades;

    for(int i=0;i<15;i++)
    {
      asteroide *a = new asteroide();
      a->settings(sRock, rand()%anchoPantalla, rand()%altoPantalla, rand()%360, 25);
      entidades.push_back(a);
    }

    player *p = new player();
    p->settings(sPlayer,400,400,0,20);
    entidades.push_back(p);







    /////main loop/////
    while (app.isOpen())
    {
        Event event;
        while (app.pollEvent(event))
        {
            if (event.type == Event::Closed)
                app.close();

            if (event.type == Event::KeyPressed)
             if (event.key.code == Keyboard::Space)
              {
                bala *b = new bala();
                b->settings(sBullet,p->x,p->y,p->angle-10,10);
                entidades.push_back(b);

                bala *b1 = new bala();
                b1->settings(sBullet,p->x,p->y,p->angle+10,10);
                entidades.push_back(b1);

                bala *b2 = new bala();
                b2->settings(sBullet5,p->x,p->y,p->angle,10);
                entidades.push_back(b2);


              }
              if (event.type == Event::KeyPressed)
              if(event.key.code == Keyboard::B){
                Disparomejorado *d = new Disparomejorado();
                d->settings(sDisparomejorado,p->x,p->y,p->angle,15);
                entidades.push_back(d);
              }

              if (event.type == Event::KeyPressed)
              if(event.key.code == Keyboard::M){
                laser *l = new laser();
                l->settings(slaserpiola,p->x,p->y,p->angle,100);
                entidades.push_back(l);
              }


              if (event.key.code == Keyboard::Escape){
                app.close();
              }
        }

    if (Keyboard::isKeyPressed(Keyboard::Right)) p->angle+=3;
    if (Keyboard::isKeyPressed(Keyboard::Left))  p->angle-=3;
    if (Keyboard::isKeyPressed(Keyboard::Up)) p->thrust=true;
    else p->thrust=false;


    for(auto a:entidades)
     for(auto b:entidades)
     {
      if (a->name=="asteroide" && b->name=="bala")
       if ( isCollide(a,b) )
           {
            a->life=false;
            b->life=false;

            Entidad *e = new Entidad();
            e->settings(sExplosion,a->x,a->y);
            e->name="explosion";
            entidades.push_back(e);


            for(int i=0;i<4;i++)
            {
             if (a->R==15) continue;
             Entidad *e = new asteroide();
             e->settings(sRock_small,a->x,a->y,rand()%360,15);
             entidades.push_back(e);
            }

           }

      if (a->name=="player" && b->name=="asteroide")
       if ( isCollide(a,b) )
           {
            if (!Keyboard::isKeyPressed(Keyboard::N)){
            b->life=false;

            Entidad *e = new Entidad();
            e->settings(sExplosion_ship,a->x,a->y);
            e->name="explosion";
            entidades.push_back(e);

            p->settings(sPlayer,anchoPantalla/2,altoPantalla/2,0,20);
            p->dx=0; p->dy=0;
            }

           }
     }

     for(auto q:entidades)
     for(auto w:entidades)
     {
      if (q->name=="asteroide" && w->name=="Disparomejorado")
       if ( isCollide(q,w) )
           {
            q->life=false;
            w->life=false;

            Entidad *e = new Entidad();
            e->settings(sExplosion,q->x,q->y);
            e->name="explosion";
            entidades.push_back(e);

           }
     }


     for(auto q:entidades)
     for(auto w:entidades)
     {
      if (q->name=="asteroide" && w->name=="laser")
       if ( isCollide(q,w) )
           {
            q->life=false;
            w->life=false;

            Entidad *e = new Entidad();
            e->settings(sExplosion,q->x,q->y);
            e->name="explosion";
            entidades.push_back(e);

           }
     }

/*
    if (p->thrust)  p->anim = sPlayer_go;
    else   p->anim = sPlayer;
*/
if (p->thrust) {p->anim = sPlayer_go;}
    else  {p->anim = sPlayer;}
    if (Keyboard::isKeyPressed(Keyboard::Left)) {
        p->anim = sPlayer_go12;
    }
    if (Keyboard::isKeyPressed(Keyboard::Right)) {
        p->anim = sPlayer_go11;
    }
  if (Keyboard::isKeyPressed(Keyboard::B)) {p->anim=sDisparomejorado;
   p->anim=sPlayer;}
   if (Keyboard::isKeyPressed(Keyboard::N)) {
        p->anim = scirculo;}

     if (Keyboard::isKeyPressed(Keyboard::M)) {
        p->anim = slaserpiola;}
//////////////////////////////////////////////////

    for(auto e:entidades)
     if (e->name=="explosion")
      if (e->anim.isEnd()) e->life=0;

    if (rand()%150==0)
     {
       asteroide *a = new asteroide();
       a->settings(sRock, 0,rand()%altoPantalla, rand()%360, 25);
       entidades.push_back(a);
     }

    for(auto i=entidades.begin();i!=entidades.end();)
    {
      Entidad *e = *i;

      e->update();
      e->anim.update();

      if (e->life==false) {i=entidades.erase(i); delete e;}
      else i++;
    }



//////////////////////






/*
      if (q->name=="player" && w->name=="asteroide")
       if ( isCollide(q,w) )
           {
            if (!Keyboard::isKeyPressed(Keyboard::N)){
            w->life=false;

            Entidad *e = new Entidad();
            e->settings(sExplosion_ship,q->x,q->y);
            e->name="explosion";
            entidades.push_back(e);

            p->settings(sPlayer,anchoPantalla/2,altoPantalla/2,0,20);
            p->dx=0; p->dy=0;
            }
           }*/







   //////draw//////
   app.draw(background);
   for(auto i:entidades) i->draw(app);
   app.display();
    }

    return 0;
}
