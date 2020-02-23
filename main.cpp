#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

class Spremnik {
    protected:
    double tezina;
    std::string naziv_sadrzaja;
    public:
    Spremnik(double tezina, std::string naziv_sadrzaja) : tezina(tezina), naziv_sadrzaja(naziv_sadrzaja) {}
    double DajTezinu() const { return tezina; }
    virtual double DajUkupnuTezinu() const=0;
    virtual void Ispisi() const=0;
    virtual Spremnik* DajKopiju() const=0;
    virtual ~Spremnik() {}
};

class Sanduk : public Spremnik {
    std::vector<double> tezine_predmeta;
    public:
    Sanduk(double tezina, std::string naziv_sadrzaja, std::vector<double> tezine_predmeta) : Spremnik(tezina, naziv_sadrzaja), tezine_predmeta(tezine_predmeta) {}
    double DajUkupnuTezinu() const override;
    void Ispisi() const override;
    Spremnik* DajKopiju() const override { return new Sanduk(*this); } 
    ~Sanduk() {}
};

class Vreca : public Spremnik {
    double tezina_materije;
    public:
    Vreca(double tezina, std::string naziv_sadrzaja, double tezina_materije) : Spremnik(tezina, naziv_sadrzaja), tezina_materije(tezina_materije) {}
    double DajUkupnuTezinu() const override { return tezina + tezina_materije; }
    void Ispisi() const override {
        std::cout << "Vrsta spremnika: Vreca\nSadrzaj: " << naziv_sadrzaja << "\nVlastita tezina: " << DajTezinu() << " (kg)\nTezina pohranjene materije: " 
            << tezina_materije << " (kg)\nUkupna tezina: " << DajUkupnuTezinu() << " (kg)" << std::endl;
    }
    Spremnik* DajKopiju() const  override { return new Vreca(*this); }
    ~Vreca() {}
};

class Bure : public Spremnik {
    double spec_tezina_tecnosti, zapremina;
    public:
    Bure(double tezina, std::string naziv_sadrzaja, double spec_tezina_tecnosti, double zapremina) : Spremnik(tezina, naziv_sadrzaja), spec_tezina_tecnosti(spec_tezina_tecnosti),
        zapremina(zapremina) {}
    double DajUkupnuTezinu() const override { return tezina + spec_tezina_tecnosti*zapremina/1000; }
    void Ispisi() const override {
        std::cout << "Vrsta spremnika: Bure\nSadrzaj: " << naziv_sadrzaja << "\nVlastita tezina: " << DajTezinu() << " (kg)\nSpecificna tezina tecnosti: " 
            << spec_tezina_tecnosti << " (kg/m^3)\nZapremina tecnosti: " << zapremina << " (l)\nUkupna tezina: " << DajUkupnuTezinu() << " (kg)" << std::endl;
    }
    Spremnik* DajKopiju() const override { return new Bure(*this); }
    ~Bure() {}
};

class PolimorfniSpremnik {
    Spremnik *p_spremnik;
    void Test() const { if(!p_spremnik) throw std::logic_error("Nespecificiran spremnik"); }
    public:
    PolimorfniSpremnik() : p_spremnik(nullptr) {}
    ~PolimorfniSpremnik() { delete p_spremnik; }
    PolimorfniSpremnik(const Spremnik &spr) : p_spremnik(spr.DajKopiju()) {}
    PolimorfniSpremnik(const PolimorfniSpremnik &spr) {
        if (!spr.p_spremnik) p_spremnik=nullptr;
        else p_spremnik = spr.p_spremnik->DajKopiju();
    }
    PolimorfniSpremnik &operator =(const PolimorfniSpremnik &spr) {
        Spremnik *p_novi=nullptr;
        if (spr.p_spremnik != nullptr) p_novi = spr.p_spremnik->DajKopiju();
        delete p_spremnik; p_spremnik = p_novi; return *this;
    }
    PolimorfniSpremnik &operator =(PolimorfniSpremnik &&spr) { std::swap(p_spremnik, spr.p_spremnik); return *this;}
    double DajTezinu() const { Test(); return p_spremnik->DajTezinu(); }
    double DajUkupnuTezinu() { Test(); return p_spremnik->DajUkupnuTezinu(); }
    void Ispisi() const { Test(); p_spremnik->Ispisi(); }
};

double Sanduk::DajUkupnuTezinu() const {
    double suma_tezina=0;
    for (const auto &el : tezine_predmeta) suma_tezina += el;
    return suma_tezina + tezina;
}

void Sanduk::Ispisi() const {
        std::cout << "Vrsta spremnika: Sanduk\nSadrzaj: " << naziv_sadrzaja << "\nTezine predmeta: ";
        for (const auto &el : tezine_predmeta) std::cout << el << " ";
        std::cout << "(kg)\nVlastita tezina: " << DajTezinu() << " (kg)\nUkupna tezina: " << DajUkupnuTezinu() << " (kg)" << std::endl;
    }

int main ()
{
	return 0;
}
