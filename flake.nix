{
    description = "ljudge with nix";

    inputs = {
        nixpkgs.url = "github:nixos/nixpkgs/nixos-25.11";
        nixpkgs-unstable.url = "github:nixos/nixpkgs/nixos-unstable";
        flake-utils.url = "github:numtide/flake-utils";
    };

    outputs = { self, nixpkgs, flake-utils, ... }@inputs:
        flake-utils.lib.eachDefaultSystem (system:
            let
                pkgs = nixpkgs.legacyPackages.${system};
            in
            {
                devShells.default = pkgs.mkShell {
                    buildInputs = with pkgs; [
                        gcc
                        gnumake
                        ruby
                        rake
                        pkg-config
                        libseccomp
                    ];
                    shellHook = ''
                        echo "🔧 C/C++ 开发环境已激活 (Make + Rake)"
                        echo "GCC: $(gcc --version | head -n1)"
                        echo "Make: $(make --version | head -n1)"
                        echo "Rake: $(rake --version)"
                    '';
                };
            });
}
