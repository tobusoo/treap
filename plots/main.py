import numpy as np
import matplotlib.pyplot as plt

data_str = "output_1.data"
data_str2 = "output_2.data"
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

ax.set(xlabel="N", ylabel="Time")
ax.grid(True, 'major', 'y')
ax.plot(n, time, label='Treap')
ax.plot(n2, time2, label='RTreap')
ax.legend(loc='center right')

plt.savefig('out.png', dpi=600)
plt.show()
