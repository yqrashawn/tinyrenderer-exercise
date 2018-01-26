#include "main.h"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red = TGAColor(255, 0, 0, 255);
const int width = 800;
const int height = 800;
// Model *model = NULL;

using namespace std;

int main(int argc, char **argv) {
  objl::Loader Loader;
  TGAImage image(width, height, TGAImage::RGB);
  bool loadout;

  if (2 == argc) {
    loadout = Loader.LoadFile(argv[1]);
  } else {
    loadout = Loader.LoadFile("model/african_head.obj");
  }

  if (loadout) {
    cout << "Model loaded\n";
    // std::ofstream file("e1Out.txt");

    // Go through each loaded mesh and out its contents
    for (int i = 0; i < Loader.LoadedMeshes.size(); i++) {
      // cout << "Current mesh is mesh " << i << "\n";
      // Copy one of the loaded meshes to be our current mesh
      objl::Mesh curMesh = Loader.LoadedMeshes[i];

      // Print Mesh Name
      // file << "Mesh " << i << ": " << curMesh.MeshName << "\n";

      // Print Vertices
      // file << "Vertices:\n";

      // Go through each vertex and print its number,
      //  position, normal, and texture coordinate
      // for (int j = 0; j < curMesh.Vertices.size(); j++) {
      //   file << "V" << j << ": "
      //        << "P(" << curMesh.Vertices[j].Position.X << ", "
      //        << curMesh.Vertices[j].Position.Y << ", "
      //        << curMesh.Vertices[j].Position.Z << ") "
      //        << "N(" << curMesh.Vertices[j].Normal.X << ", "
      //        << curMesh.Vertices[j].Normal.Y << ", "
      //        << curMesh.Vertices[j].Normal.Z << ") "
      //        << "TC(" << curMesh.Vertices[j].TextureCoordinate.X << ", "
      //        << curMesh.Vertices[j].TextureCoordinate.Y << ")\n";
      // }

      cout << curMesh.Vertices.size() << "\n";
      for (int j = 0; j < curMesh.Vertices.size() - 1; j += 3) {
        int x0 = (curMesh.Vertices[j].Position.X + 1) * width / 2;
        int y0 = (curMesh.Vertices[j].Position.Y + 1) * height / 2;
        int x1 = (curMesh.Vertices[j + 1].Position.X + 1) * width / 2;
        int y1 = (curMesh.Vertices[j + 1].Position.Y + 1) * height / 2;
        line(x0, y0, x1, y1, image, white);
        x1 = (curMesh.Vertices[j + 2].Position.X + 1) * width / 2;
        y1 = (curMesh.Vertices[j + 2].Position.Y + 1) * height / 2;
        line(x0, y0, x1, y1, image, white);
        x0 = (curMesh.Vertices[j + 1].Position.X + 1) * width / 2;
        y0 = (curMesh.Vertices[j + 1].Position.Y + 1) * height / 2;
        line(x0, y0, x1, y1, image, white);
      }

      int x0 = (curMesh.Vertices[curMesh.Vertices.size() - 1].Position.X + 1) *
               width / 2;
      int y0 = (curMesh.Vertices[curMesh.Vertices.size() - 1].Position.Y + 1) *
               height / 2;
      int x1 = (curMesh.Vertices[0].Position.X + 1) * width / 2;
      int y1 = (curMesh.Vertices[0].Position.Y + 1) * height / 2;
    }

    // file.close();
  } else {
    cout << "load model failed\n";
  }

  image.flip_vertically(); // i want to have the origin at the left bottom
  // corner of the image

  image.write_tga_file("output.tga");
  return 0;
}

void line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color) {
  bool steep = false;
  if (abs(x0 - x1) < abs(y0 - y1)) {
    swap(x0, y0);
    swap(x1, y1);
    steep = true;
  }
  if (x0 > x1) {
    swap(x0, x1);
    swap(y0, y1);
  }
  int dx = x1 - x0;
  int dy = y1 - y0;
  int derror2 = abs(dy) * 2;
  int error2 = 0;
  int y = y0;
  for (int x = x0; x <= x1; x++) {
    if (steep) {
      image.set(y, x, color);
    } else {
      image.set(x, y, color);
    }
    error2 += derror2;
    if (error2 > dx) {
      y += (y1 > y0 ? 1 : -1);
      error2 -= dx * 2;
    }
  }
}