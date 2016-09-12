#ifndef DRAWABLE_OBJECT_H
#define DRAWABLE_OBJECT_H

#include <float.h>
#include "lib/common/point.h"


/**
 * @interface DrawableObject
 * @brief L'interfaccia DrawableObject modella un oggetto renderizzabile da una GLcanvas.
 *
 * Contiene dei metodi che devono essere implementati dalle classi che ereditano da DrawableObject
 * per essere renderizzate da una GLcanvas.
 *
 * @author Marco Livesu (marco.livesu@gmail.com)
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 * @copyright Marco Livesu 2014.
 */
class DrawableObject
{
    public :

        DrawableObject() {}                      /**< @brief Costruttore, vuoto */

        virtual void  draw()          const = 0; /**< @brief Disegna l'oggetto mediante chiamate OpenGL */
        virtual Pointd sceneCenter()  const = 0; /**< @brief Restituisce la posizione del centro dell'oggetto */
        virtual float sceneRadius()   const = 0; /**< @brief Restituisce il raggio della bounding sphere dell'oggetto */
        virtual bool isVisible()      const = 0; /**< @brief Restituisce true se l'oggetto è visibile, false altrimenti */
        virtual void setVisible(bool)       = 0; /**< @brief Setta la visibilità dell'oggetto */
};

#endif // DRAWABLE_OBJECT_H
