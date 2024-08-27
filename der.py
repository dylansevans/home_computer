class Der:
    def __init__(self, termData):
        self.terms = []
        for term in termData:
            if term[1] == 0:
                continue
            else:
                coeff = term[0] * term[1]
                power = term[1] - 1
                self.terms.append([coeff, power])
        self.finalCheck = (len(self.terms) != 1)