/**
 * @file        filler.cpp
 * @description Implementation of functions in the filler namespace.
 *
 *              SUBMIT THIS FILE WITH YOUR MODIFICATIONS
 */

/**
 * Performs a flood fill using breadth first search.
 *
 * @param config FillerConfig struct to setup the fill
 * @return animation object illustrating progression of flood fill algorithm
 */
animation filler::FillBFS(FillerConfig& config) {
    return Fill<Queue>(config);
}



/**
 * Performs a flood fill using depth first search.
 *
 * @param  config - FillerConfig struct to setup the fill
 * @return animation object illustrating progression of flood fill algorithm
 */
animation filler::FillDFS(FillerConfig& config) {
    return Fill<Stack>(config);
}




/**
 * Run a flood fill on an image starting at the seed point
 *
 * @param config FillerConfig struct with data for flood fill of image
 * @return animation object illustrating progression of flood fill algorithm
 */
template <template <class T> class OrderingStructure> animation filler::Fill(FillerConfig& config)
{
    animation anim;
    OrderingStructure<PixelPoint> os; 
    vector<vector<bool>> processed(config.img.height(), vector<bool>(config.img.width(), false)); // Tracking processed pixels

    RGBAPixel seedColor = *config.img.getPixel(config.seedpoint.x, config.seedpoint.y);
    os.Add(config.seedpoint);
    processed[config.seedpoint.y][config.seedpoint.x] = true;

    int pixelsProcessed = 0;
    while (!os.IsEmpty()) {
        PixelPoint p = os.Remove();
        RGBAPixel* pixel = config.img.getPixel(p.x, p.y);
        *pixel = config.picker->operator()(p); 

        int dx[] = {1, 0, -1, 0};
        int dy[] = {0, 1, 0, -1};

        for (int i = 0; i < 4; ++i) {
            int nx = p.x + dx[i], ny = p.y + dy[i];
            if (nx >= 0 && nx < config.img.width() && ny >= 0 && ny < config.img.height() && !processed[ny][nx]) {
                RGBAPixel* nextPixel = config.img.getPixel(nx, ny);
                if (nextPixel->distanceTo(seedColor) <= config.tolerance) {
                    os.Add(PixelPoint(nx, ny));
                    processed[ny][nx] = true;
                }
            }
        }

        pixelsProcessed++;
        if (pixelsProcessed % config.frameFreq == 0 || os.IsEmpty()) {
            anim.addFrame(config.img);
        }
    }

    return anim;
}

void processNeighbor(int x, int y, OrderingStructure<PixelPoint>& os, vector<vector<bool>>& visited, const filler::FillerConfig& config) {
    if (x < 0 || y < 0 || x >= config.img.width() || y >= config.img.height() || visited[y][x])
        return;
    RGBAPixel* currentPixel = config.img.getPixel(x, y);
    RGBAPixel* seedPixel = config.img.getPixel(config.seedpoint.x, config.seedpoint.y);
    if (currentPixel->distanceTo(*seedPixel) <= config.tolerance) {
        os.Add(PixelPoint(x, y, *currentPixel));
        visited[y][x] = true;
    }
}



