import * as ts from './typescript'

const exampleCode = `
export function greet(name: string): string {
    return \`Hello, \${name}!\`;
}
`;

const parsedFile = ts.createSourceFile('example.ts',exampleCode,ts.ScriptTarget.JSON)

console.log(parsedFile)

