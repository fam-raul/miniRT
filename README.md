*This project has been created as part of the 42 curriculum by atanimot[,rmainaga].*

# miniRT

## Description

`miniRT` is a minimal ray tracer written in C, using the MiniLibX library, developed
as part of the 42 common core. It renders a static 3D scene described in a `.rt` text
file — one ambient light, one camera, one light source, and any number of spheres,
planes and cylinders — into a window, using ambient and diffuse lighting with hard
shadows.

This repository contains the mandatory part only (no bonus features).

## Instructions

### Build

```bash
make
```

The Makefile first builds the bundled `minilibx-linux` library, then compiles the
project.

### Run

```bash
./miniRT scenes/minimal.rt
```

The program takes exactly one argument: the path to a `.rt` scene file.

- `ESC` or the window's close button exits the program cleanly.
- Any malformed scene file makes the program print `Error` followed by an explicit
  message, and exit without opening a window.

### Clean

```bash
make clean   # remove object files
make fclean  # also remove the binary
make re      # fclean + all
```

### Regression tests

```bash
./scripts/test_scenes.sh                # valid/invalid scenes, checks Error/no-Error behaviour
./scripts/check_correction_mandatory.sh # a 14-scene mandatory-focused pack
./scripts/review_correction_cases.sh    # opens the same 14 scenes one by one for visual review
```

Sample scenes are provided under `scenes/`:
- `scenes/tests_valid/*.rt` — scenes expected to render without error
- `scenes/tests_invalid/*` — scenes expected to be rejected with `Error`
- `scenes/correction_mandatory/*.rt` — scenes covering common mandatory evaluation
  points (shapes, translation/rotation, camera axes, brightness, shadows)

### Features

- `.rt` scene parser with strict identifiers and validation:
  - `A` ambient light (ratio + color), `C` camera (position, orientation, FOV),
    `L` light (position, brightness ratio, color) — each allowed only once
  - `sp` sphere, `pl` plane, `cy` cylinder (finite, with both caps)
  - ratios in `[0.0, 1.0]`, colors in `[0, 255]`, normalized orientation vectors,
    strictly positive diameters/heights
  - elements may appear in any order, separated by one or more spaces/line breaks
- Ray tracing:
  - arbitrarily positioned/oriented sphere, plane and cylinder, correctly handling
    views from inside an object
  - camera with an arbitrary orientation vector and a configurable horizontal field
    of view
- Lighting:
  - ambient lighting (objects are never fully black)
  - diffuse lighting scaled by the light's brightness ratio
  - hard shadows
- Window: the image is rendered once into an MLX image and displayed; `ESC` and the
  window's close button both exit cleanly; switching/minimizing the window stays
  responsive since nothing re-renders on every event.

### Scene format

Each non-empty line begins with an identifier; elements may appear in any order.

- Ambient: `A ratio R,G,B`
- Camera: `C x,y,z  dx,dy,dz  fov`
- Light: `L x,y,z  ratio  R,G,B`
- Sphere: `sp x,y,z  diameter  R,G,B`
- Plane: `pl x,y,z  nx,ny,nz  R,G,B`
- Cylinder: `cy x,y,z  ax,ay,az  diameter  height  R,G,B`

## Resources

- MiniLibX documentation: `minilibx-linux/README.md` and the man pages under
  `minilibx-linux/man/`
- Scratchapixel — "Ray Tracing: Generating Camera Rays" and "A Minimal Ray-Tracer":
  background on ray/sphere and ray/plane intersections and the Phong lighting model
- Wikipedia — "Ray tracing (graphics)" and "Phong reflection model"

### AI usage

AI assistance (Claude) was used to review this implementation against the project
subject. It pointed out that this README did not follow the subject's required
structure, that three functions (`parse_int`, `ft_strncmp`, `trim_line`) were
declared and defined but never called anywhere in the mandatory part, and that the
diffuse shading term incorrectly used the light's R, G, B color even though the
subject marks that value as unused in the mandatory part. It was also used to
explain the ray-tracing pipeline (camera basis, ray generation, sphere/plane/cylinder
intersection, ambient/diffuse/shadow shading) line by line for the project defense.
The suggested fixes were reviewed and understood before being applied.
