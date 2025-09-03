import { Server } from "@modelcontextprotocol/sdk/server/index.js";
import { StdioServerTransport } from "@modelcontextprotocol/sdk/server/stdio.js";
import {
  ListToolsRequestSchema,
  CallToolRequestSchema,
} from "@modelcontextprotocol/sdk/types.js";

const server = new Server(
  { name: "hello-mcp", version: "0.1.0" },
  {
    capabilities: {
      tools: {},
    },
  }
);

const tools = [
  {
    name: "echo",
    description: "Echo back the provided text.",
    inputSchema: {
      type: "object",
      properties: {
        text: { type: "string", description: "Text to echo back" },
      },
      required: ["text"],
    },
  },
  {
    name: "time",
    description: "Get the current ISO timestamp.",
    inputSchema: { type: "object", properties: {} },
  },
];

// List tools handler
server.setRequestHandler(ListToolsRequestSchema, async (_request) => {
  return { tools };
});

// Call tool handler
server.setRequestHandler(CallToolRequestSchema, async (request) => {
  const { name, arguments: args = {} } = request.params;
  if (name === "echo") {
    const text = typeof args.text === "string" ? args.text : "";
    return { content: [{ type: "text", text }] };
  }
  if (name === "time") {
    const now = new Date().toISOString();
    return { content: [{ type: "text", text: now }] };
  }
  return {
    content: [{ type: "text", text: `Unknown tool: ${name}` }],
    isError: true,
  };
});

const transport = new StdioServerTransport();
server
  .connect(transport)
  .then(() => {
    // Server is now listening on stdio
  })
  .catch((err) => {
    console.error("Failed to start hello-mcp server:", err);
    process.exit(1);
  });
