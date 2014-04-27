import numpy as np

def lambda1(T, J, h):
    return np.exp(J/T)*np.cosh(h/T)+np.sqrt(np.exp(2.0*J/T)*(np.sinh(h/T)**2)+np.exp(-2.0*J/T))

def lambda1der(T, J, h):
    return h*np.exp(J/T)*np.sinh(h/T)+J*np.exp(J/T)*np.cosh(h/T)+(h*np.exp(2.0*J/T)*np.sinh(h/T)*np.cosh(h/T)-J*np.exp(-2.0*J/T))/(np.sqrt(2.0*J/T)*(np.sinh(h/T)**2)+np.exp(-2.0*J/T))

def energy(T, J=None, h=None):
    if h is None:
        return -J*np.tanh(J/T)
    elif J is None:
        return -h*np.tanh(h/T)
    else:
        return -lambda1der(T, J, h)/lambda1(T, J, h)

def magnetization(h, T=None, J=None):
    if J is None:
        return np.tanh(h/T)
    else:
        return np.sinh(h/T)/np.sqrt((np.sinh(h/T)**2)+np.exp(-4*J/T))
