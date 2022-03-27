return {
  version = "1.5",
  luaversion = "5.1",
  tiledversion = "1.8.2",
  orientation = "orthogonal",
  renderorder = "right-down",
  width = 10,
  height = 10,
  tilewidth = 100,
  tileheight = 100,
  nextlayerid = 2,
  nextobjectid = 1,
  properties = {},
  tilesets = {
    {
      name = "COLOR_TEST_PNG",
      firstgid = 1,
      filename = "COLOR_TEST_PNG.tsx",
      exportfilename = "COLOR_TEST_PNG.lua"
    },
    {
      name = "TestTile",
      firstgid = 25,
      filename = "TestTile.tsx",
      exportfilename = "TestTile.lua"
    }
  },
  layers = {
    {
      type = "tilelayer",
      x = 0,
      y = 0,
      width = 10,
      height = 10,
      id = 1,
      name = "Слой тайлов 1",
      visible = true,
      opacity = 1,
      offsetx = 0,
      offsety = 0,
      parallaxx = 1,
      parallaxy = 1,
      properties = {},
      encoding = "lua",
      data = {
        27, 0, 0, 0, 0, 0, 0, 0, 0, 6,
        0, 27, 0, 0, 0, 0, 0, 0, 6, 0,
        0, 0, 27, 0, 0, 0, 0, 6, 0, 0,
        0, 0, 0, 27, 0, 0, 6, 0, 0, 0,
        0, 0, 0, 0, 27, 6, 0, 0, 0, 0,
        0, 0, 0, 0, 6, 27, 0, 0, 0, 0,
        0, 0, 0, 6, 0, 0, 27, 0, 0, 0,
        0, 0, 6, 0, 0, 0, 0, 27, 0, 0,
        0, 6, 0, 0, 0, 0, 0, 0, 27, 0,
        6, 0, 0, 0, 0, 0, 0, 0, 0, 27
      }
    }
  }
}
