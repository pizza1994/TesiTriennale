#ifndef DCEL_POINT_H
#define DCEL_POINT_H

/**
 * @mainpage Common Classes and Structures
 * La cartella common contiene alcune classi, interfacce e strutture che sono comunemente usate in altre classi.
 * Nella cartella sono contenute le classi e interfacce:
 * - Point
 * - BoundingBox
 * - DrawableObject
 *
 * Inoltre sono contenute le strutture:
 * - cmpQColor
 */

#include <sstream>
#include <assert.h>
#include <QDebug>
#include <string>
#include <iostream>
#include <math.h>

/**
 * @class Point
 * @brief La classe Point modella un punto o un vettore nell spazio.
 *
 * Rappresenta un punto o vettore in 3 dimensioni, con precisione dati variabile definita dal tipo T.
 * In particolare, è possibile avere punti/vettori con precisione intera, float o double.
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
template <class T> class Point {

    public:

        /****************
         * Constructors *
         ****************/

        Point(T xCoord = 0.0, T yCoord = 0.0, T zCoord = 0.0);
        virtual ~Point(void){}

        /*************************
        * Public Inline Methods *
        *************************/

        T x()                                               const;
        T y()                                               const;
        T z()                                               const;
        double dist(const Point<T>& otherPoint)             const;
        T dot(const Point<T>& otherVector)                  const;
        Point<T> cross(const Point<T>& otherVector)         const;
        double getLength()                                  const;
        double getLengthSquared()                           const;
        Point<T> min(const Point<T>& otherPoint)            const;
        Point<T> max(const Point<T>& otherPoint)            const;
        bool operator == (const Point<T>& otherPoint)       const;
        bool operator != (const Point<T>& otherPoint)       const;
        bool operator < (const Point<T>& otherPoint)        const;
        Point<T> operator - ()                              const;
        Point<T> operator + (const Point<T>& otherPoint)    const;
        Point<T> operator - (const Point<T>& otherPoint)    const;
        Point<T> operator * (const T& scalar)               const;
        Point<T> operator * (const Point<T>& otherPoint)    const;
        Point<T> operator / (const T& scalar )              const;
        Point<T> operator / (const Point<T>& otherPoint)    const;

        void setX(const T& x);
        void setY(const T& y);
        void setZ(const T& z);
        void set(const T& x, const T& y, const T& z);
        double normalize();
        void rotate(double matrix[3][3], const Point<T>& centroid = Point<T>());
        Point<T> operator += (const Point<T>& otherPoint);
        Point<T> operator -= (const Point<T>& otherPoint);
        Point<T> operator *= (const T& scalar);
        Point<T> operator *= (const Point<T>& otherPoint);
        Point<T> operator /= (const T& scalar );
        Point<T> operator /= (const Point<T>& otherPoint);
        std::ostream& operator << (std::ostream& inputStream);

        /*****************
        * Public Methods *
        ******************/

        std::string toString() const;

    protected:

        /**************
        * Attributes *
        **************/

        T xCoord; /**< @brief La componente x del punto/vettore */
        T yCoord; /**< @brief La componente y del punto/vettore */
        T zCoord; /**< @brief La componente z del punto/vettore */
};

/****************
* Other Methods *
*****************/

template <class T>
Point<T> operator * (const T& scalar, const Point<T>& point);

/**************
* Other Types *
***************/

typedef Point<float>  Pointf; /**< @brief Point composto da componenti float */
typedef Point<double> Pointd; /**< @brief Point composto da componenti double */
typedef Point<int>    Pointi; /**< @brief Point composto da componenti int */
typedef Point<double> Vec3;   /**< @brief Point composto da componenti double, zucchero sintattico per distinguere punti da vettori */

/****************
 * Constructors *
 ****************/

/**
 * @brief Costruttore, inizializza il punto con i valori in input
 * @param[in] x: valore componente x, default 0
 * @param[in] y: valore componente y, default 0
 * @param[in] z: valore componente z, default 0
 */
template <class T>
inline Point<T>::Point(T x, T y, T z) : xCoord(x), yCoord(y), zCoord(z) {
}

/*************************
* Public Inline Methods *
*************************/

/**
 * @brief Restituisce la componente x del punto/vettore this
 * @return La componente x
 */
template <class T>
inline T Point<T>::x() const {
    return this->xCoord;
}

/**
 * @brief Restituisce la componente y del punto/vettore this
 * @return La componente y
 */
template <class T>
inline T Point<T>::y() const {
    return this->yCoord;
}

/**
 * @brief Restituisce la componente z del punto/vettore this
 * @return La componente z
 */
template <class T>
inline T Point<T>::z() const {
    return this->zCoord;
}

/**
 * @brief Funzione per il calcolo della distanza euclidea tra due punti
 * @param[in] otherPoint: punto su cui viene calcolata la distanza
 * @return La distanza euclidea tra this e otherPoint
 */
template <class T>
inline double Point<T>::dist(const Point<T>& otherPoint) const {
    return sqrt ( pow((xCoord - otherPoint.xCoord), 2) +
                  pow((yCoord - otherPoint.yCoord), 2) +
                  pow((zCoord - otherPoint.zCoord), 2) );
}

/**
 * @brief Funzione per il calcolo del prodotto scalare tra due vettori
 * @param[in] otherVector: vettore con cui viene calcolato il prodotto scalare
 * @return Il prodotto scalare tra this e otherVector
 */
template <class T>
inline T Point<T>::dot(const Point<T>& otherVector) const {
    return xCoord * otherVector.xCoord +
           yCoord * otherVector.yCoord +
           zCoord * otherVector.zCoord;
}

/**
 * @brief Funzione per il calcolo del prodotto vettoriale tra due vettori
 * @param[in] otherVector: vettore con cui viene calcolato il prodotto vettoriale
 * @return Il prodotto vettoriale tra this e otherVector
 */
template <class T>
inline Point<T> Point<T>::cross(const Point<T>& otherVector) const {
    return Point(yCoord * otherVector.zCoord - zCoord * otherVector.yCoord,
                 zCoord * otherVector.xCoord - xCoord * otherVector.zCoord,
                 xCoord * otherVector.yCoord - yCoord * otherVector.xCoord);
}

/**
 * @brief Funzione per il calcolo della lunghezza di un vettore
 * @return La lunghezza del vettore this
 */
template <class T>
inline double Point<T>::getLength() const {
    return sqrt( xCoord*xCoord + yCoord*yCoord + zCoord*zCoord );
}

/**
 * @brief Operatore per il calcolo della lunghezza al quadrato di un vettore
 * @return La lunghezza al quadrato del vettore this
 */
template <class T>
inline double Point<T>::getLengthSquared() const {
    return xCoord * xCoord + yCoord * yCoord + zCoord * zCoord;
}

/**
 * @brief Funzione di minimo tra punti/vettori.
 *
 * Ogni componente del punto/vettore restituito sarà uguale alla corrispondente componente minore tra il punto/vettore
 * this e otherPoint.
 *
 * @param[in] otherPoint: punto/vettore con cui viene calcolata la funzione di minimo
 *
 * @return Il punto/vettore dei minimi
 */
template <class T>
inline Point<T> Point<T>::min(const Point<T>& otherPoint) const {
    return Point<T>(std::min(x(), otherPoint.x()),
                    std::min(y(), otherPoint.y()),
                    std::min(z(), otherPoint.z()));
}

/**
 * @brief Funzione di massimo tra punti/vettori.
 *
 * Ogni componente del punto/vettore restituito sarà uguale alla corrispondente componente maggiore tra il punto/vettore
 * this e otherPoint.
 *
 * @param[in] otherPoint: punto/vettore con cui viene calcolata la funzione di massimo
 *
 * @return Il punto/vettore dei massimi
 */
template <class T>
inline Point<T> Point<T>::max(const Point<T>& otherPoint) const {
    return Point<T>(std::max(x(), otherPoint.x()),
                    std::max(y(), otherPoint.y()),
                    std::max(z(), otherPoint.z()));
}

/**
 * @brief Operatore di uguaglianza tra punti/vettori.
 *
 * Due punti/vettori sono considerati uguali se tutte e tre le loro componenti sono uguali.
 *
 * @param[in] otherPoint: punto/vettore con cui viene verificata l'uguaglianza
 * @return True se il punto e otherPoint sono uguali, false altrimenti
 */
template <class T>
inline bool Point<T>::operator == (const Point<T>& otherPoint) const {
    if ( otherPoint.xCoord != xCoord )	return false;
    if ( otherPoint.yCoord != yCoord )	return false;
    if ( otherPoint.zCoord != zCoord )	return false;
    return true;
}

/**
 * @brief Operatore di disuguaglianza tra punti/vettori.
 *
 * Due punti/vettori sono considerati diversi se almeno una delle loro componenti è diversa.
 *
 * @param[in] otherPoint: punto/vettore con cui viene verificata la disuguaglianza
 * @return True se il punto e otherPoint sono diversi, false altrimenti
 */
template <class T>
inline bool Point<T>::operator != (const Point<T>& otherPoint) const {
    if ( otherPoint.xCoord != xCoord )	return true;
    if ( otherPoint.yCoord != yCoord )	return true;
    if ( otherPoint.zCoord != zCoord )	return true;
    return false;
}

/**
 * @brief Operatore di minore tra punti/vettori.
 *
 * In questo contesto, il punto/vettore è minore di otherPoint se la sua componente x
 * è minore di quella di otherPoint; in caso di uguaglianza si verifica la componente y
 * e in caso di ultieriore uguaglianza la componente z.
 *
 * @param[in] otherPoint: altro punto/vettore
 * @return True se il punto/vettore this è minore di otherPoint, false altrimenti
 */
template <class T>
inline bool Point<T>::operator < (const Point<T>& otherPoint) const {
    if (this->xCoord < otherPoint.xCoord) return true;
    if (this->xCoord > otherPoint.xCoord) return false;
    if (this->yCoord < otherPoint.yCoord) return true;
    if (this->yCoord > otherPoint.yCoord) return false;
    if (this->zCoord < otherPoint.zCoord) return true;
    return false;
}

/**
 * @brief Operatore prefisso di negazione, restituisce il punto/vettore negato
 * @return Il punto/vettore negato
 */
template <class T>
inline Point<T> Point<T>::operator - () const {
    return Point<T>(-xCoord, -yCoord, -zCoord);
}

/**
 * @brief Operatore di somma tra punti/vettori
 * @param[in] otherPoint: punto/vettore con cui verrà sommato il punto/vettore this
 * @return Il punto/vettore risultato della somma, componente per componente, tra i punti/vettori this e otherPoint
 */
template <class T>
inline Point<T> Point<T>::operator + (const Point<T>& otherPoint) const {
    return Point<T>(xCoord + otherPoint.xCoord,
                    yCoord + otherPoint.yCoord,
                    zCoord + otherPoint.zCoord);
}

/**
 * @brief Operatore di sottrazione tra punti/vettori
 * @param[in] otherPoint: punto/vettore che verrà sottratto al punto/vettore this
 * @return Il punto/vettore risultato della differenza, componente per componente, tra i punti/vettori this e otherPoint
 */
template <class T>
inline Point<T> Point<T>::operator - (const Point<T>& otherPoint) const {
    return Point<T>(xCoord - otherPoint.xCoord,
                    yCoord - otherPoint.yCoord,
                    zCoord - otherPoint.zCoord);
}

/**
 * @brief Operatore di prodotto scalare tra un punto/vettore e uno scalare
 * @param[in] scalar: scalare con cui verrà eseguito il prodotto scalare
 * @return Il punto/vettore risultato del prodotto scalare tra tra il punto/vettore this e scalar
 */
template <class T>
inline Point<T> Point<T>::operator * (const T& scalar) const {
    return Point<T>(xCoord * scalar, yCoord * scalar, zCoord * scalar);
}

/**
 * @brief Operatore di prodotto, componente per componente, tra punti/vettori
 * @param[in] otherPoint: punto/vettore con cui verrà eseguito il prodotto
 * @return Il punto/vettore risultato del prodotto, componente per componente, tra i punti/vettori this e otherPoint
 */
template <class T>
inline Point<T> Point<T>::operator * (const Point<T>& otherPoint) const {
    return Point<T>(xCoord * otherPoint.xCoord, yCoord * otherPoint.yCoord, zCoord * otherPoint.zCoord);
}

/**
 * @brief Operatore di quoziente scalare tra un punto/vettore e uno scalare
 * @param[in] scalar: scalare con cui verrà eseguito il quoziente scalare
 * @return Il punto/vettore risultato del quoziente scalare tra il punto/vettore this e scalar
 */
template <class T>
inline Point<T> Point<T>::operator / (const T& scalar) const {
    return Point<T>(xCoord / scalar, yCoord / scalar, zCoord / scalar);
}

/**
 * @brief Operatore di quoziente, componente per componente, tra punti/vettori
 * @param[in] otherPoint: punto/vettore con cui verrà eseguito il quoziente
 * @return Il punto/vettore risultato del quoziente, componente per componente, tra i punti/vettori this e otherPoint
 */
template <class T>
inline Point<T> Point<T>::operator / (const Point<T>& otherPoint) const {
    return Point<T>(xCoord / otherPoint.xCoord, yCoord / otherPoint.yCoord, zCoord / otherPoint.zCoord);
}

/**
 * @brief Modifica la componente x del punto/vettore this
 * @param[in] x: valore settato come componente x
 */
template <class T>
inline void Point<T>::setX(const T& x) {
    xCoord = x;
}

/**
 * @brief Modifica la componente y del punto/vettore this
 * @param[in] y: valore settato come componente y
 */
template <class T>
inline void Point<T>::setY(const T& y) {
    yCoord = y;
}

/**
 * @brief Modifica la componente z del punto/vettore this
 * @param[in] z: valore settato come componente z
 */
template <class T>
inline void Point<T>::setZ(const T& z) {
    zCoord = z;
}

/**
 * @brief Modifica le componenti del punto/vettore this
 * @param[in] x: valore settato come componente x
 * @param[in] y: valore settato come componente y
 * @param[in] z: valore settato come componente z
 */
template <class T>
inline void Point<T>::set(const T& x, const T& y, const T& z) {
    xCoord = x;
    yCoord = y;
    zCoord = z;
}

/**
 * @brief Funzione di normalizzazione di un vettore, in modo tale che la sua lunghezza sia pari a 1
 * @return La lunghezza precedente del vettore prima di essere normalizzato
 */
template <class T>
inline double Point<T>::normalize() {
    double len = getLength();
    xCoord /= len;
    yCoord /= len;
    zCoord /= len;
    return len;
}

/**
 * @brief Applica una matrice di rotazione 3x3 ad un punto/vettore
 * @param[in] m: matrice di rotazione 3x3
 * @param[in] centroid: punto centroide della rotazione, di default (0,0,0)
 */
template <class T>
inline void Point<T>::rotate(double matrix[3][3], const Point<T>& centroid) {
    this -= centroid;
    rotate(matrix);
    this += centroid;
}

/**
 * @brief Operatore di somma e assegnamento tra punti/vettori.
 *
 * Il risultato della somma è assegnato al punto/vettore this.
 *
 * @param[in] otherPoint: punto/vettore con cui verrà sommato il punto/vettore this
 * @return Il punto/vettore risultato della somma, componente per componente, tra i punti/vettori this e otherPoint
 */
template <class T>
inline Point<T> Point<T>::operator += (const Point<T>& otherPoint) {
    xCoord += otherPoint.xCoord;
    yCoord += otherPoint.yCoord;
    zCoord += otherPoint.zCoord;
    return *this;
}

/**
 * @brief Operatore di sottrazione e assegnamento tra punti/vettori.
 *
 * Il risultato della differenza è assegnato al punto/vettore this.
 *
 * @param[in] otherPoint: punto/vettore che verrà sottratto al punto/vettore this
 * @return Il punto/vettore risultato della differenza, componente per componente, tra i punti/vettori this e otherPoint
 */
template <class T>
inline Point<T> Point<T>::operator -= (const Point<T>& otherPoint) {
    xCoord -= otherPoint.xCoord;
    yCoord -= otherPoint.yCoord;
    zCoord -= otherPoint.zCoord;
    return *this;
}

/**
 * @brief Operatore di prodotto scalare e assegnamento tra un punto/vettore e uno scalare.
 *
 * Il risultato del prodotto scalare è assegnato al punto/vettore this.
 *
 * @param[in] scalar: scalare con cui verrà eseguito il prodotto scalare
 * @return Il punto/vettore risultato del prodotto scalare tra tra il punto/vettore this e scalar
 */
template <class T>
inline Point<T> Point<T>::operator *= (const T& scalar) {
    xCoord *= scalar;
    yCoord *= scalar;
    zCoord *= scalar;
    return *this;
}

/**
 * @brief Operatore di prodotto, componente per componente, e assegnamento tra punti/vettori.
 *
 * Il risultato del prodotto è assegnato al punto/vettore this.
 *
 * @param[in] otherPoint: punto/vettore con cui verrà eseguito il prodotto
 * @return Il punto/vettore risultato del prodotto, componente per componente, tra i punti/vettori this e otherPoint
 */
template <class T>
inline Point<T> Point<T>::operator *= (const Point<T>& otherPoint) {
    xCoord *= otherPoint.xCoord;
    yCoord *= otherPoint.yCoord;
    zCoord *= otherPoint.zCoord;
    return *this;
}

/**
 * @brief Operatore di quoziente scalare e assegnamento tra un punto/vettore e uno scalare.
 *
 * Il risultato del quoziente scalare è assegnato al punto/vettore this.
 *
 * @param[in] scalar: scalare con cui verrà eseguito il quoziente scalare
 * @return Il punto/vettore risultato del quoziente scalare tra il punto/vettore this e scalar
 */
template <class T>
inline Point<T> Point<T>::operator /= (const T& scalar) {
    xCoord /= scalar;
    yCoord /= scalar;
    zCoord /= scalar;
    return *this;
}

/**
 * @brief Operatore di quoziente, componente per componente, e assegnamento tra punti/vettori.
 *
 * Il risultato del quoziente è assegnato al punto/vettore this.
 *
 * @param[in] otherPoint: punto/vettore con cui verrà eseguito il quoziente
 * @return Il punto/vettore risultato del quoziente, componente per componente, tra i punti/vettori this e otherPoint
 */
template <class T>
inline Point<T> Point<T>::operator /= (const Point<T>& otherPoint) {
    xCoord /= otherPoint.xCoord;
    yCoord /= otherPoint.yCoord;
    zCoord /= otherPoint.zCoord;
    return *this;
}

/**
 * @brief Operatore di stram sul punto/vettore
 * @param[in] input_stream: stream di input
 * @return Lo stream di input a cui è stato accodato lo stream del punto/vettore
 */
template <class T>
inline std::ostream& Point<T>::operator << (std::ostream& inputStream) {
    inputStream << "[" << xCoord << ", " << yCoord << ", " << zCoord << "]";
    return inputStream;
}

/*****************
* Public Methods *
******************/

/**
 * @brief Funzione toString di un punto/vettore
 * @return Una stringa rappresentativa del punto/vettore this
 */
template <class T>
std::string Point<T>::toString() const {
    std::stringstream ss;
    ss << this;
    std::string s1 = ss.str();
    return s1;
}

/****************
* Other Methods *
*****************/
/**
 * @brief Operatore di prodotto scalare tra un punto/vettore e uno scalare
 * @param[in] scalar: scalare con cui verrà eseguito il prodotto scalare
 * @param[in] point: punto/vettore con cui verrà eseguito il prodotto scalare
 * @return Il punto/vettore risultato del prodotto scalare tra tra point e scalar
 */
template <class T>
inline Point<T> operator * (const T& scalar, const Point<T>& point) {
    return Point<T>(point.xCoord * scalar,
                    point.yCoord * scalar,
                    point.zCoord * scalar);
}

#endif // DCEL_POINT_H
