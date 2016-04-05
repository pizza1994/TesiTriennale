#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H

#pragma once

#include <float.h>
#include "point.h"

/**
 * @class BoundingBox
 * @brief La classe BoundingBox modella un Bounding Box contenente una mesh 3D.
 *
 *        Essa è caratterizzata da due punti contenenti le tre coordinate minime e massime che generano il bounding box.
 *        La classe fornisce metodi come il calcolo del centro e il calcolo della diagonale.
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 * @author Marco Livesu (marco.livesu@gmail.com)
 */
class BoundingBox {
    public:

        /****************
         * Constructors *
         ****************/

        BoundingBox();
        BoundingBox(const Pointd& min, const Pointd& max);

        /************************
        * Public Inline Methods *
        *************************/

        Pointd getMin()     const;
        Pointd getMax()     const;
        double getMinX()    const;
        double getMinY()    const;
        double getMinZ()    const;
        double getMaxX()    const;
        double getMaxY()    const;
        double getMaxZ()    const;
        Pointd  center()    const;
        double diag()       const;

        void setMin(const Pointd& min);
        void setMax(const Pointd& max);
        void setMin(double x, double y, double z);
        void setMax(double x, double y, double z);
        void setMinX(double x);
        void setMinY(double y);
        void setMinZ(double z);
        void setMaxX(double x);
        void setMaxY(double y);
        void setMaxZ(double z);
        void reset();

    protected:

        /**************
        * Attributes *
        **************/

        Pointd min; /**< @brief Punto minimo del bounding box */
        Pointd max; /**< @brief Punto massimo del bounding box */

};

/****************
 * Constructors *
 ****************/

/**
 * @brief Costruttore, crea un bounding box e chiama il metodo reset()
 */
inline BoundingBox::BoundingBox() {
    reset();
}

/**
 * @brief Costruttore, crea un bounding box con limite minimo min e limite massimo max
 * @param[in] min: punto minimo che verrà settato
 * @param[in] max: punto massimo che verrà settato
 */
inline BoundingBox::BoundingBox(const Pointd& min, const Pointd& max) : min(min), max(max) {
}

/*************************
* Public Inline Methods *
*************************/

/**
 * @brief Restituisce il punto minimo del bounding box
 * @return Il punto minimo
 */
inline Pointd BoundingBox::getMin() const {
    return min;
}

/**
 * @brief Restituisce il punto massimo del bounding box
 * @return Il punto massimo
 */
inline Pointd BoundingBox::getMax() const {
    return max;
}

/**
 * @brief Restituisce la componente x del punto minimo del bounding box
 * @return La componente x del punto minimo
 */
inline double BoundingBox::getMinX() const {
    return min.x();
}

/**
 * @brief Restituisce la componente y del punto minimo del bounding box
 * @return La componente y del punto minimo
 */
inline double BoundingBox::getMinY() const {
    return min.y();
}

/**
 * @brief Restituisce la componente z del punto minimo del bounding box
 * @return La componente z del punto minimo
 */
inline double BoundingBox::getMinZ() const {
    return min.z();
}

/**
 * @brief Restituisce la componente x del punto massimo del bounding box
 * @return La componente x del punto massimo
 */
inline double BoundingBox::getMaxX() const {
    return max.x();
}

/**
 * @brief Restituisce la componente y del punto massimo del bounding box
 * @return La componente y del punto massimo
 */
inline double BoundingBox::getMaxY() const {
    return max.y();
}

/**
 * @brief Restituisce la componente z del punto massimo del bounding box
 * @return La componente z del punto massimo
 */
inline double BoundingBox::getMaxZ() const {
    return max.z();
}

/**
 * @brief Calcola il centro del bounding box
 * @return Il punto al centro del bounding box
 */
inline Pointd BoundingBox::center() const {
    return (min + max) * 0.5;
}

/**
 * @brief Calcola la lunghezza della diagonale del bounding box
 * @return La lunghezza della diagonale del bounding box
 */
inline double BoundingBox::diag() const {
    return (min - max).getLength();
}

/**
 * @brief Modifica il punto minimo del bounding box
 * @param[in] min: punto settato come punto minimo
 */
inline void BoundingBox::setMin(const Pointd& min) {
    this->min = min;
}

/**
 * @brief Modifica il punto massimo del bounding box
 * @param[in] min: punto settato come punto massimo
 */
inline void BoundingBox::setMax(const Pointd& max) {
    this->max = max;
}

/**
 * @brief Modifica il punto minimo del bounding box
 * @param[in] x: valore settato come componente x del punto minimo
 * @param[in] y: valore settato come componente y del punto minimo
 * @param[in] z: valore settato come componente z del punto minimo
 */
inline void BoundingBox::setMin(double x, double y, double z) {
    min.set(x, y, z);
}

/**
 * @brief Modifica il punto massimo del bounding box
 * @param[in] x: valore settato come componente x del punto massimo
 * @param[in] y: valore settato come componente y del punto massimo
 * @param[in] z: valore settato come componente z del punto massimo
 */
inline void BoundingBox::setMax(double x, double y, double z) {
    max.set(x, y, z);
}

/**
 * @brief Modifica la componente x del punto minimo del bounding box
 * @param[in] x: valore settato come componente x del punto minimo
 */
inline void BoundingBox::setMinX(double x) {
    min.setX(x);
}

/**
 * @brief Modifica la componente y del punto minimo del bounding box
 * @param[in] y: valore settato come componente y del punto minimo
 */
inline void BoundingBox::setMinY(double y) {
    min.setY(y);
}

/**
 * @brief Modifica la componente z del punto minimo del bounding box
 * @param[in] z: valore settato come componente z del punto minimo
 */
inline void BoundingBox::setMinZ(double z) {
    min.setZ(z);
}

/**
 * @brief Modifica la componente x del punto massimo del bounding box
 * @param[in] x: valore settato come componente x del punto massimo
 */
inline void BoundingBox::setMaxX(double x) {
    max.setX(x);
}

/**
 * @brief Modifica la componente y del punto massimo del bounding box
 * @param[in] y: valore settato come componente y del punto massimo
 */
inline void BoundingBox::setMaxY(double y) {
    max.setY(y);
}

/**
 * @brief Modifica la componente z del punto massimo del bounding box
 * @param[in] z: valore settato come componente z del punto massimo
 */
inline void BoundingBox::setMaxZ(double z) {
    max.setZ(z);
}

/**
 * \brief Resetta il bounding box.
 *
 * Setta le tre componenti del punto minimo a FLT_MAX, e le tre componenti del punto massimo a -FLT_MAX.
 */
inline void BoundingBox::reset() {
    min = Pointd( FLT_MAX,  FLT_MAX,  FLT_MAX);
    max = Pointd(-FLT_MAX, -FLT_MAX, -FLT_MAX);
}

#endif // BOUNDING_BOX_H
