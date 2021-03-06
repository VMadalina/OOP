//
// Created by Madalina on 12/11/2020.
//

#include "../includes/Traseu_marcat.h"

Traseu_marcat::Traseu_marcat(const Traseu& t, const Marcaj& m, int poz) {
    this->marcaj = m;
    this->pozitie = poz;
    this->set_alt_init(t.get_alt());
    this->set_alt_max(t.get_alt_max());
}

Traseu_marcat::Traseu_marcat(const Marcaj& m, int poz) {
    this->marcaj = m;
    this->pozitie = poz;
}

float Traseu_marcat:: timp_traseu () {
    float ore = this->Traseu::timp_traseu() - 0.1;
    return ore;
}

std::ostream& operator << (std::ostream& out, Traseu_marcat& tm) {
    out <<"Traseul ales este amenajat, cu marcajul " << tm.marcaj.get_forma() << " " << tm.marcaj.get_culoare() << ".\n";
    return out;
}

Traseu_marcat &Traseu_marcat::operator = (Marcaj &m) {
    this->marcaj.set_culoare(m.get_culoare());
    this->marcaj.set_forma(m.get_forma());
    return (*this);
}