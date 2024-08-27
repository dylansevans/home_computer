from der import Der
from formatting import FormatPoly

class Polynomial:
    def __init__(self, coefficientAndExp):
        self.derivatives = []
        self.termData = coefficientAndExp
        termsToAdd = FormatPoly({
            "terms": coefficientAndExp,
            "finalCheck": True
        })
        while termsToAdd.finalCheck == True:
            self.derivatives.append(termsToAdd["terms"])
            derivative = Der(termsToAdd.terms)
            termsToAdd = FormatPoly(Polynomial(derivative))

    def eval(self, x):
        print("evaluate create function")