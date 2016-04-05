#ifndef CMP_QCOLOR
#define CMP_QCOLOR

#include <QColor>

/**
 * @struct cmpQColor
 * @brief La struttura cmpQColor implementa un comparatore per classe QColor.
 *
 * È in grado di stabilire se un QColor è minore di un altro o meno, ordinando rispettivamente per componente
 * red, poi green e poi blue. Può essere utilizzato come parametro nel caso in cui si voglia usare un QColor su
 * una struttura dati che necessita di un ordinamento.
 *
 * @example std::map<QColor, int, cmpQColor> map;
 */
struct cmpQColor {
    bool operator()(const QColor& a, const QColor& b) const {
        if (a == b) return false;
        if (a.red() == b.red() && a.green() == b.green()) return (a.blue() < b.blue());
        if (a.red() == b.red()) return (a.green() < b.green());
        return (a.red() < b.red());
    }
};

/**
 * @struct cmpUnorderedStdPair
 * @brief la struttura @cmpUnorderedStdPair implementa un comparatore per la classe std::pair<T,T>
 *
 * Confronta una coppia di elementi e stabilisce se una è minore dell'altra senza tener conto dell'ordine
 * degli elementi. Può essere utilizzato come parametro nel caso in cui si voglia usare un QColor su
 * una struttura dati che necessita di un ordinamento.
 * Può essere utile se si vuole fare in modo che in un insieme di coppie non si possano avere due coppie c
 * on gli stessi elementi invertiti.
 *
 * @example La coppia (0,2) non risulta essere minore della coppia (2,0).
 * @example la coppia (2,0) risulta essere minore della coppia (0,3).
 * @example std::set<std::pair<int, int>, cmpUnorderedStdPair<int> > set;
 */
template <class T>
struct cmpUnorderedStdPair {
    bool operator()(const std::pair<T,T>& a, const std::pair<T,T>& b) const {
        T amin, bmin, amax, bmax;
        if (a.first < a.second) {
            amin = a.first;
            amax = a.second;
        }
        else {
            amin = a.second;
            amax = a.first;
        }
        if (b.first < b.second){
            bmin = b.first;
            bmax = b.second;
        }
        else {
            bmin = b.second;
            bmax = b.first;
        }
        if (amin < bmin) return true;
        else if (amin == bmin) return (amax < bmax);
        return false;
    }
};

#endif // CMP_QCOLOR

