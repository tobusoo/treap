import numpy as np
import matplotlib.pyplot as plt

data_str = "output_3.data"
data_str2 = "output_4.data"
print(data_str)
print(data_str2)

data = np.loadtxt(data_str)
data2 = np.loadtxt(data_str2)

n = data[:, 0]
time = data[:, 1]

n2 = data2[:, 0]
time2 = data2[:, 1]

fig, ax = plt.subplots(1, 1)
fig.set_size_inches(11, 7)

ax.set(xlabel="Количество элементов в словаре",
       ylabel="Время поиска элемента, с")
ax.grid(True, 'major', 'y')
ax.plot(n, time, label='Treap worst case')
ax.plot(n2, time2, label='Bstree worst case')
ax.legend(loc='center right')

out_path = 'out2.svg'
plt.savefig(out_path, dpi=600)
print(f'Saved to {out_path}')
