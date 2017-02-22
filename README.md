# XLowPoly
Low poly picture, Sandpainting for Android implemented by JNI, delaunay triangulation algorithm.

## Screenshots

<img src="/screenshots/lowpoly0.png" alt="screenshot" title="screenshot" width="270" height="486" /> <img src="/screenshots/lowpoly1.png" alt="screenshot" title="screenshot" width="270" height="486" />

<img src="/screenshots/lowpoly2.png" alt="screenshot" title="screenshot" width="270" height="486" /> <img src="/screenshots/lowpoly3.png" alt="screenshot" title="screenshot" width="270" height="486" />

## Including in your project

To add a dependency on xlowpoly using Gradle:

```gradle
dependencies {
  compile 'io.github.xyzxqs:xlowpoly:1.0.1'
}
```

or import the module `xlowpoly` to your project by Android Studio

You can also use [these source files](./xlowpoly/src/main/cpp/) to compile cross platform program.

## Usage

```java

Bitmap out = LowPoly.sandPainting(Bitmap input, int threshold, float alphaOrPointCount);

Bitmap out = LowPoly.lowPoly(Bitmap input, float alphaOrPointCount, boolean fill); 

```

## License

     Copyright 2016 xyzxqs (xyzxqs@gmail.com)

     Licensed under the Apache License, Version 2.0 (the "License");
     you may not use this file except in compliance with the License.
     You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

     Unless required by applicable law or agreed to in writing, software
     distributed under the License is distributed on an "AS IS" BASIS,
     WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
     See the License for the specific language governing permissions and
     limitations under the License.
