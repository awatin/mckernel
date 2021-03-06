Background and Motivation
=========================

With the growing complexity of high-end supercomputers, the current
system software stack faces significant challenges as we move forward to
exascale and beyond. The necessity to deal with extreme degree of
parallelism, heterogeneous architectures, multiple levels of memory
hierarchy, power constraints, etc., advocates operating systems that can
rapidly adapt to new hardware requirements, and that can support novel
programming paradigms and runtime systems. On the other hand, a new
class of more dynamic and complex applications are also on the horizon,
with an increasing demand for application constructs such as in-situ
analysis, workflows, elaborate monitoring and performance tools. This
complexity relies not only on the rich features of POSIX, but also on
the Linux APIs (such as the */proc*, */sys* filesystems, etc.) in
particular.

Two Traditional HPC OS Approaches
---------------------------------

Traditionally, light-weight operating systems specialized for HPC
followed two approaches to tackle scalable execution of large-scale
applications. In the full weight kernel (FWK) approach, a full Linux
environment is taken as the basis, and features that inhibit attaining
HPC scalability are removed, i.e., making it light-weight. The pure
light-weight kernel (LWK) approach, on the other hand, starts from
scratch and effort is undertaken to add sufficient functionality so that
it provides a familiar API, typically something close to that of a
general purpose OS, while at the same time it retains the desired
scalability and reliability attributes. Neither of these approaches
yields a fully Linux compatible environment.

The Multi-kernel Approach
-------------------------

A hybrid approach recognized recently by the system software community
is to run Linux simultaneously with a lightweight kernel on compute
nodes and multiple research projects are now pursuing this direction.
The basic idea is that simulations run on an HPC tailored lightweight
kernel, ensuring the necessary isolation for noiseless execution of
parallel applications, but Linux is leveraged so that the full POSIX API
is supported. Additionally, the small code base of the LWK can also
facilitate rapid prototyping for new, exotic hardware features.
Nevertheless, the questions of how to share node resources between the
two types of kernels, where do device drivers execute, how exactly do
the two kernels interact with each other and to what extent are they
integrated, remain subjects of ongoing debate.
