FROM artemisbeta/geant4
RUN apt update -y
COPY . /simvue/
RUN python3 -m pip install /simvue/
RUN cp /simvue/examples/Geant4/DMX.cc /usr/local/share/geant4/install/4.11.2/share/Geant4/examples/advanced/underground_physics/
RUN cmake -DCMAKE_PREFIX_PATH=/usr/local/share/geant4/install/4.11.2/ -B/simvue/build /usr/local/share/geant4/install/4.11.2/share/Geant4/examples/advanced/underground_physics/
RUN cmake --build /simvue/build
