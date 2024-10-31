Vagrant.configure("2") do |config|
    config.vm.define "bbrahimS" do |server|
      server.vm.box = "generic/ubuntu1804"  
      server.vm.hostname = "bbrahimS"
      server.vm.synced_folder ".", "/ft_shield"
      server.vm.network "private_network", ip: "192.168.56.110"
      server.vm.provision "shell", inline: <<-SHELL
        sudo apt-get update
        sudo apt-get install -y make gcc upx
      SHELL
      server.vm.provider "virtualbox" do |vb|
        vb.memory = 512
        vb.cpus = 1
      end
    end
  end