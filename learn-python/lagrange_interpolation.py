class DefFunction:
    def __init__(self, points):
        self.points = []
        self.knownX = []
        for point in points:
            newPoint = {
                "x": point[0],
                "y": point[1],
            }
            self.knownX.append(point[0])
            self.points.append(newPoint)
        
        for i in self.points:
            weight = 1
            for j in self.points:
                if i["x"] == j["x"]:
                    continue
                else:
                    weight /= (i["x"] - j["x"])
            i["w"] = weight
    
    def l(self, x):
        value = 1
        for p in self.points:
            value *= (x - p["x"])

        return value



    def eval(self, x):
        if x in self.knownX:
            for point in self.points:
                if point["x"] == x:
                    return point["y"]
        else:
            tallyParts = 0
            for point in self.points:
                val = point["w"] * point["y"]/ (x - point["x"])
                tallyParts += val
            
            tallyParts *= self.l(x)

            return tallyParts
        
func = DefFunction([[12,13], [33,49], [-6,4], [7,12]])

print(func.eval(6))