import sys
import matplotlib.pyplot as plt
from matplotlib.patches import Rectangle

nombre_archivo = sys.argv[1] if len(sys.argv) > 1 else "salida.txt"

ancho = 100.0
alto = 100.0
obstaculos = []
trayectorias = {}
colisiones = []

with open(nombre_archivo) as archivo:
    for linea in archivo:
        partes = linea.split()
        if len(partes) == 0 or partes[0].startswith("#"):
            continue

        etiqueta = partes[0]

        if etiqueta == "CAJA":
            ancho = float(partes[1])
            alto = float(partes[2])

        elif etiqueta == "OBSTACULO":
            obstaculos.append((float(partes[2]), float(partes[3]),
                               float(partes[4]), float(partes[5])))

        elif etiqueta == "POS":
            id_particula = int(partes[2])
            if id_particula not in trayectorias:
                trayectorias[id_particula] = ([], [])
            trayectorias[id_particula][0].append(float(partes[3]))
            trayectorias[id_particula][1].append(float(partes[4]))

        elif etiqueta == "COL_PARED_ELASTICA":
            colisiones.append(("PARED", float(partes[3]), float(partes[4])))

        elif etiqueta == "COL_OBSTACULO_INELASTICA":
            colisiones.append(("OBSTACULO", float(partes[6]), float(partes[7])))

        elif etiqueta == "FUSION_COMPLETAMENTE_INELASTICA":
            colisiones.append(("FUSION", float(partes[5]), float(partes[6])))

fig, ax = plt.subplots(figsize=(8, 8))

ax.add_patch(Rectangle((0, 0), ancho, alto, fill=False, edgecolor="black", linewidth=2))
for (ox, oy, ow, oh) in obstaculos:
    ax.add_patch(Rectangle((ox, oy), ow, oh, color="gray"))

for id_particula in sorted(trayectorias):
    xs, ys = trayectorias[id_particula]
    linea, = ax.plot(xs, ys, linewidth=1.2, label="Particula " + str(id_particula))
    ax.plot(xs[0], ys[0], "o", color=linea.get_color())

estilos = {
    "PARED": ("x", "Colision con pared (elastica)"),
    "OBSTACULO": ("^", "Colision con obstaculo (inelastica)"),
    "FUSION": ("*", "Fusion de particulas (completamente inelastica)"),
}
for tipo in estilos:
    xs = [c[1] for c in colisiones if c[0] == tipo]
    ys = [c[2] for c in colisiones if c[0] == tipo]
    if len(xs) > 0:
        ax.plot(xs, ys, estilos[tipo][0], color="black", markersize=9,
                linestyle="None", label=estilos[tipo][1])

margen = 0.05 * max(ancho, alto)
ax.set_xlim(-margen, ancho + margen)
ax.set_ylim(-margen, alto + margen)
ax.set_aspect("equal")
ax.set_xlabel("Posicion X")
ax.set_ylabel("Posicion Y")
ax.set_title("Simulacion de colisiones multiples")
ax.legend(loc="upper left", bbox_to_anchor=(1.02, 1))

plt.tight_layout()
plt.savefig("grafica.png", dpi=150)
plt.show()
