gcc src/main.c src/engine.c src/textures.c src/camera.c src/player.c src/components/script.c src/components/transform.c src/components/sprite.c src/components/animsprite.c src/components/rigidbody.c -lraylib -lbox2d -o build/game
cd build
./game
cd ..