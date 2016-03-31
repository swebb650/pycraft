typedef union {
    struct {
        float r;
        float g;
        float b;
    };
    struct {
        float h;
        float s;
        float v;
    };
} Colour;


bool
colour_eq(Colour *a, Colour *b)
{
    return (a->r == b->r &&
            a->g == b->g &&
            a->b == b->b);
}


float
lerp(float a, float s, float b)
{
    return a * (1 - s) + (b * s);
}

void
lerp_colour(Colour *a, float s, Colour *b, Colour *result)
{
    result->r = lerp(a->r, s, b->r);
    result->g = lerp(a->g, s, b->g);
    result->b = lerp(a->b, s, b->b);
}

void
rgb_to_hsv(Colour *rgb, Colour *hsv)
{
    float min = fmin(rgb->r, fmin(rgb->g, rgb->b));
    float max = fmax(rgb->r, fmin(rgb->g, rgb->b));
    hsv->v = max;

    float delta = max - min;

    if (max != 0)
    {
        hsv->s = delta / max;

        if (delta == 0)
            hsv->h = 0;
        else if (rgb->r == max)
            hsv->h = (rgb->g - rgb->b) / delta;      // between yellow & magenta
        else if (rgb->g == max)
            hsv->h = 2 + (rgb->b - rgb->r) / delta;  // between cyan & yellow
        else
            hsv->h = 4 + (rgb->r - rgb->g) / delta;  // between magenta & cyan

        hsv->h *= 60;

        if (hsv->h < 0)
            hsv->h += 360;
    }
    else
    {
        hsv->s = 0;
        hsv->h = -1;
    }
}

void
hsv_to_rgb(Colour *hsv, Colour *rgb)
{
    int i;
    float f, p, q, t;

    if (hsv->s == 0)
    {
        rgb->r = rgb->g = rgb->b = hsv->v;  // Grey
        return;
    }

    hsv->h /= 60;
    i = floor(hsv->h);
    f = hsv->h - i;
    p = hsv->v * (1 - hsv->s);
    q = hsv->v * (1 - hsv->s * f);
    t = hsv->v * (1 - hsv->s * (1 - f));

    switch (i) {
        case 0:
            rgb->r = hsv->v;
            rgb->g = t;
            rgb->b = p;
            break;
        case 1:
            rgb->r = q;
            rgb->g = hsv->v;
            rgb->b = p;
            break;
        case 2:
            rgb->r = p;
            rgb->g = hsv->v;
            rgb->b = t;
            break;
        case 3:
            rgb->r = p;
            rgb->g = q;
            rgb->b = hsv->v;
            break;
        case 4:
            rgb->r = t;
            rgb->g = p;
            rgb->b = hsv->v;
            break;
        default:
            rgb->r = hsv->v;
            rgb->g = p;
            rgb->b = q;
            break;
    }
}


int
grey(float value)
{
    return 232 + (int)(value * 23);
}


int
rgb(Colour *c)
{
    int rgb;
    if (c->r == c->g && c->g == c->b)
    {
        rgb = grey(c->r);
    }
    else
    {
        rgb = 16 + (int)(c->r*5)*36 + (int)(c->g*5)*6 + (int)(c->b*5);
    }

    return rgb;
}


char *
colour_str(wchar_t character, Colour bg, Colour fg, int style)
{
    return (char *)0;
}
