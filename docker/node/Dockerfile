FROM ubuntu
MAINTAINER Kevin Killingsworth <kevin@redfenix.com>

RUN apt-get update

# install nodejs and npm
RUN apt-get install -y nodejs npm git git-core

# install the node app and dependencies
ADD install_node_app.sh /tmp/
RUN chmod +x /tmp/install_node_app.sh
RUN ./tmp/install_node_app.sh

# node test server
EXPOSE 8080

# run the node server
ADD run_node_app.sh /tmp/
RUN chmod +x /tmp/run_node_app.sh
CMD /tmp/run_node_app.sh

